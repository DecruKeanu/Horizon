#include "MiniginPCH.h"
#include "TriggerComponent.h"
#include "TransformComponent.h"
#include "TriggerManager.h"
#include "Renderer.h"

Horizon::TriggerComponent::TriggerComponent(GameObject* pParent, const Horizon::IRect& collisionRect) : Component(pParent),
m_CollisionRect{ collisionRect },
m_OffsetX{ collisionRect.x },
m_OffsetY{ collisionRect.y },
m_pOverlappingActors{}
{
	m_CallBackFunction = [](GameObject*, GameObject*, TriggerAction, std::string) {};
}

Horizon::TriggerComponent::TriggerComponent(GameObject* pParent, const std::string& identifier, const Horizon::IRect& collisionRect) : Component(pParent, identifier),
m_CollisionRect{ collisionRect },
m_OffsetX{ collisionRect.x },
m_OffsetY{ collisionRect.y },
m_pOverlappingActors{}
{
	m_CallBackFunction = [](GameObject*, GameObject*, TriggerAction, std::string) {};
}

void Horizon::TriggerComponent::SetOnTriggerCallBack(const CallBackFunction& function)
{
	m_CallBackFunction = function;
}

void Horizon::TriggerComponent::OverlapsWith(TriggerComponent* pOtherTrigger)
{
	const auto it = std::find_if(m_pOverlappingActors.begin(), m_pOverlappingActors.end(), [pOtherTrigger,this](const OverlapData& overlapData) {return (pOtherTrigger->Equals(overlapData.pTrigger)); });

	if (it != m_pOverlappingActors.end())
	{
		it->IsOverlapping = true;
		return;
	}

	if (pOtherTrigger->GetParent()->GetIsActive() == false)
		return;

	const OverlapData currentOverlap = OverlapData{ pOtherTrigger, true };

	m_pOverlappingActors.push_back(currentOverlap);
	m_CallBackFunction(m_pGameObject, currentOverlap.pTrigger->GetParent(), TriggerAction::Enter, currentOverlap.pTrigger->GetIdentifier());

}

const Horizon::IRect& Horizon::TriggerComponent::GetCollisionRect() const
{
	return m_CollisionRect;
}

const size_t Horizon::TriggerComponent::GetOverlappingActorsSize()
{
	return m_pOverlappingActors.size();
}

void Horizon::TriggerComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	if (m_pTransformComponent == nullptr)
	{
		Horizon::Logger::LogWarning("TriggerComponent::Initialize >> GameObject does not have transformComponent");
		return;
	}

	m_CollisionRect.x = m_pTransformComponent->GetPosition().x + m_OffsetX;
	m_CollisionRect.y = m_pTransformComponent->GetPosition().y + m_OffsetY;

	m_pOverlappingActors.reserve(4);

	TriggerManager::GetInstance().AddTriggerComponent(this);
}

void Horizon::TriggerComponent::Update()
{
	//remove_if places all elements that fullfil the predicament to the end of the vector and returns the iterator to the first element
	const auto it = std::remove_if(m_pOverlappingActors.begin(), m_pOverlappingActors.end(), [](const OverlapData& overlapData)
		{
			return !overlapData.IsOverlapping;
		});

	for (auto idx{ it }; idx < m_pOverlappingActors.end(); ++idx)
	{
		m_CallBackFunction(m_pGameObject, idx->pTrigger->GetParent(), TriggerAction::Exit, it->pTrigger->GetIdentifier());
	}

	m_pOverlappingActors.erase(it, m_pOverlappingActors.end());

	for (OverlapData& overlapData : m_pOverlappingActors)
	{
		overlapData.IsOverlapping = false;
	}

	m_CollisionRect.x = m_pTransformComponent->GetPosition().x + m_OffsetX;
	m_CollisionRect.y = m_pTransformComponent->GetPosition().y + m_OffsetY;
}

void Horizon::TriggerComponent::Render() const
{
	const bool visualise = false;

	if (!visualise)
		return;

	const SDL_Rect sdlRect = { m_CollisionRect.x, m_CollisionRect.y, m_CollisionRect.width, m_CollisionRect.height };
	const SDL_Color red = { 255,0,0,255 };
	const SDL_Color green = { 0,255,0,255 };
	const SDL_Color& color = m_pOverlappingActors.empty() ? red : green;

	Renderer::GetInstance().DrawSDLRect(color, &sdlRect);
}

