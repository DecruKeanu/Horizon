#include "GamePCH.h"
#include "PlayerDiscComponent.h"
#include "PlayerInputComponent.h"
#include "MovementComponent.h"
#include <TransformComponent.h>
#include <Timer.h>

using namespace Horizon;

PlayerDiscComponent::PlayerDiscComponent(Horizon::GameObject* pGameObject) : Component(pGameObject),
m_OriginalPoint{},
m_ElapsedTime{},
m_IsPlayerOnFlyingDisc{},
m_IsFallingOfFlyingDisc{}
{

}

void PlayerDiscComponent::PlayerOnDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent)
{
	m_OriginalPoint = m_pPlayerTransformComponent->GetPosition();
	m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	m_pPlayerInputComponent->DeactivateInput();
	m_pFlyingDiscTransformComponent = pFlyingDiscTransformComponent;
	m_IsPlayerOnFlyingDisc = true;
}

void PlayerDiscComponent::Initialize()
{
	m_pPlayerMovementComponent = m_pGameObject->GetComponent<MovementComponent>();
	m_pPlayerTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pPlayerInputComponent = m_pGameObject->GetComponent<PlayerInputComponent>();
}

void PlayerDiscComponent::Update()
{
	PlayerStandingOnDisc();
	PlayerFallingOfDisc();
}

void PlayerDiscComponent::PlayerStandingOnDisc()
{
		if (!m_IsPlayerOnFlyingDisc)
		return;

	const IPoint2 playerOffset = { 2,-22 };
	const IPoint2 desiredPos = { 310 + playerOffset.x,32 + playerOffset.y };

	if (m_pPlayerTransformComponent->GetPosition() != desiredPos)
		m_pPlayerTransformComponent->SetPosition(m_pFlyingDiscTransformComponent->GetPosition().x + playerOffset.x, m_pFlyingDiscTransformComponent->GetPosition().y + playerOffset.y);
	else
	{
		m_ElapsedTime = 0.f;
		m_IsFallingOfFlyingDisc = true;
		m_IsPlayerOnFlyingDisc = false;
		m_OriginalPoint = desiredPos;

		m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	}
}

void PlayerDiscComponent::PlayerFallingOfDisc()
{
	if (!m_IsFallingOfFlyingDisc)
		return;

	const IPoint2 desiredPos = { 307,57 };

	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();

	if (HelperFunctions::MoveToLerpedPos(m_OriginalPoint, desiredPos, m_ElapsedTime, m_pPlayerTransformComponent))
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = desiredPos;
		m_IsFallingOfFlyingDisc = false;

		m_pPlayerInputComponent->ResetInput();

		m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	}
}