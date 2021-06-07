#include "GamePCH.h"

#include "FlyingDiscMovementComponent.h"
#include <TransformComponent.h>

#include <Timer.h>
#include <SoundSystemServiceLocator.h>

FlyingDiscMovementComponent::FlyingDiscMovementComponent(Horizon::GameObject* pParent) : Component(pParent),
m_OriginalPos{},
m_ElapsedTime{},
m_IsActive{}
{

}

void FlyingDiscMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_OriginalPos = { m_pTransformComponent->GetPosition().x,m_pTransformComponent->GetPosition().y };
}

void FlyingDiscMovementComponent::Update()
{
	if (!m_IsActive)
		return;

	const float lerpTime = 2.f;
	m_ElapsedTime = std::min(lerpTime, m_ElapsedTime + Horizon::Timer::GetInstance().GetDeltaTime());

	const Horizon::IPoint2 desiredPos = { 310,32 };
	const Horizon::IPoint2 currentPos = Horizon::MathHelper::IPoint2Lerp(m_OriginalPos, desiredPos, m_ElapsedTime / lerpTime);

	m_pTransformComponent->SetPosition(currentPos);

	(currentPos == desiredPos) ? m_pGameObject->Deactivate() : void();
}

void FlyingDiscMovementComponent::Activate()
{
	m_IsActive = true;
}
