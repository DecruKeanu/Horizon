#include "MiniginPCH.h"
#include "TriggerComponent.h"
#include "TransformComponent.h"
#include "TriggerManager.h"
#include "Renderer.h"

Horizon::TriggerComponent::TriggerComponent(GameObject* pParent, const Horizon::IRect& collisionRect) : Component(pParent),
	m_CollisionRect{collisionRect},
	m_pOverlappingActors{}
{
	m_CallBackFunction = [](GameObject*, GameObject*, TriggerAction) {};
}

void Horizon::TriggerComponent::SetOnTriggerCallBack(const CallBackFunction& function)
{
	m_CallBackFunction = function;
}

void Horizon::TriggerComponent::OverlapsWith(GameObject* pGameObject)
{
	const auto it = std::find_if(m_pOverlappingActors.begin(), m_pOverlappingActors.end(), [pGameObject](const OverlapData& overlapData) {return (pGameObject->Equals(overlapData.pOverlapObject)); });

	if (it != m_pOverlappingActors.end())
	{
		it->IsOverlapping = true;
		return;
	}

	m_pOverlappingActors.push_back(OverlapData{ pGameObject, true });
	m_CallBackFunction(m_pGameObject, pGameObject, TriggerAction::Enter);
}

const Horizon::IRect& Horizon::TriggerComponent::GetCollisionRect() const
{
	return m_CollisionRect;
}

void Horizon::TriggerComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	if (m_pTransformComponent == nullptr)
	{
		Horizon::Logger::LogWarning("TriggerComponent::Initialize >> QBert does not have transformComponent");
		return;
	}

	m_CollisionRect.x = m_pTransformComponent->GetPosition().x;
	m_CollisionRect.y = m_pTransformComponent->GetPosition().y;

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
		m_CallBackFunction(m_pGameObject, idx->pOverlapObject, TriggerAction::Exit);
	}

	m_pOverlappingActors.erase(it,m_pOverlappingActors.end());

	for (OverlapData& overlapData : m_pOverlappingActors)
	{
		overlapData.IsOverlapping = false;
	}

	m_CollisionRect.x = m_pTransformComponent->GetPosition().x;
	m_CollisionRect.y = m_pTransformComponent->GetPosition().y;
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

