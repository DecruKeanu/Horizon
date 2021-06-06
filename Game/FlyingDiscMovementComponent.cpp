#include "GamePCH.h"
#include "FlyingDiscMovementComponent.h"
#include <TransformComponent.h>
#include <SoundSystemServiceLocator.h>
#include <Timer.h>

using namespace Horizon;

FlyingDiscMovementComponent::FlyingDiscMovementComponent(Horizon::GameObject* pParent) : Component(pParent),
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
	m_OriginalPos = { m_pTransformComponent->GetPosition().x,m_pTransformComponent->GetPosition().y };
}

void FlyingDiscMovementComponent::Update()
{
	if (!m_IsActive)
		return;

	const float lerpTime = 2.f;
	m_ElapsedTime = std::min(lerpTime, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	const IPoint2 desiredPos = { 310,32 };
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPos, desiredPos, m_ElapsedTime / lerpTime);

	m_pTransformComponent->SetPosition(currentPos);

	if (currentPos == desiredPos)
		m_pGameObject->Deactivate();
}
