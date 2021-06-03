#include "GamePCH.h"
#include "FlyingDiscMovementComponent.h"
#include <TransformComponent.h>
#include <Timer.h>
#include <MathHelper.h>

using namespace Horizon;

FlyingDiscMovementComponent::FlyingDiscMovementComponent(Horizon::GameObject* pParent) : Component(pParent),
m_DesiredPos{},
m_OriginalPos{},
m_ElapsedTime{},
m_Turns{},
m_IsActive{}
{

}

void FlyingDiscMovementComponent::Activate()
{
	m_IsActive = true;
}

void FlyingDiscMovementComponent::Deactivate()
{
	m_IsActive = false;
}

void FlyingDiscMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_DesiredPos = { 310,32 };
	m_OriginalPos = { m_pTransformComponent->GetPosition().x,m_pTransformComponent->GetPosition().y };
}

void FlyingDiscMovementComponent::Update()
{
	if (!m_IsActive)
		return;

	const float lerpTime = 2.f;
	m_ElapsedTime = std::min(lerpTime, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPos, m_DesiredPos, m_ElapsedTime / lerpTime);

	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y, 0);

	if (currentPos.x == m_DesiredPos.x && currentPos.y == m_DesiredPos.y)
	{
		m_pGameObject->Deactivate();
		//m_ElapsedTime = 0.f;
		//m_Turns++;
		//std::swap(m_OriginalPos, m_DesiredPos);

		//if (m_Turns == 2)
		//{
		//	m_Turns = 0;
		//	Deactivate();
		//}
	}
}
