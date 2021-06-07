#include "GamePCH.h"
#include "PlayerDiscComponent.h"

#include "MovementComponent.h"
#include "PlayerInputComponent.h"
#include <TransformComponent.h>

#include <Timer.h>
#include <SoundSystemServiceLocator.h>

PlayerDiscComponent::PlayerDiscComponent(Horizon::GameObject* pGameObject) : Component(pGameObject),
m_OriginalPoint{},
m_ElapsedTime{},
m_IsPlayerOnFlyingDisc{},
m_IsFallingOfFlyingDisc{}
{

}

void PlayerDiscComponent::Initialize()
{
	m_pPlayerMovementComponent = m_pGameObject->GetComponent<MovementComponent>();
	m_pPlayerTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pPlayerInputComponent = m_pGameObject->GetComponent<PlayerInputComponent>();
}

void PlayerDiscComponent::Update()
{
	PlayerStandingOnDisc();
	PlayerFallingOfDisc();
}

void PlayerDiscComponent::PlayerOnDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent)
{
	m_OriginalPoint = m_pPlayerTransformComponent->GetPosition();

	m_pPlayerInputComponent->DeactivateInput();
	m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	m_pFlyingDiscTransformComponent = pFlyingDiscTransformComponent;

	if (!m_IsPlayerOnFlyingDisc)
		Horizon::SoundSystemServiceLocator::GetSoundSystem().QueueEvent(6, 36);

	m_IsPlayerOnFlyingDisc = true;
}

bool PlayerDiscComponent::PlayerOnDisc() const
{
	return m_IsPlayerOnFlyingDisc;
}



void PlayerDiscComponent::PlayerStandingOnDisc()
{
	if (!m_IsPlayerOnFlyingDisc)
		return;

	const Horizon::IPoint2 playerOffset = { 2,-22 };
	const Horizon::IPoint2 desiredPos = { 310 + playerOffset.x,32 + playerOffset.y };

	const Horizon::IPoint2 currentPos = { m_pFlyingDiscTransformComponent->GetPosition().x + playerOffset.x, m_pFlyingDiscTransformComponent->GetPosition().y + playerOffset.y };

	if (currentPos.x == desiredPos.x)
	{
		m_ElapsedTime = 0.f;
		m_IsFallingOfFlyingDisc = true;
		m_IsPlayerOnFlyingDisc = false;
		m_OriginalPoint = desiredPos;

		m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	}
	else
	{
		m_pPlayerTransformComponent->SetPosition(m_pFlyingDiscTransformComponent->GetPosition().x + playerOffset.x, m_pFlyingDiscTransformComponent->GetPosition().y + playerOffset.y);
	}
}


void PlayerDiscComponent::PlayerFallingOfDisc()
{
	if (!m_IsFallingOfFlyingDisc)
		return;

	const Horizon::IPoint2 desiredPos = { 307,57 };

	m_ElapsedTime += Horizon::Timer::GetInstance().GetDeltaTime();

	if (HelperFunctions::MoveToLerpedPos(m_OriginalPoint, desiredPos, m_ElapsedTime, m_pPlayerTransformComponent))
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = desiredPos;
		m_IsFallingOfFlyingDisc = false;

		m_pPlayerInputComponent->ActivateInput();

		m_pPlayerMovementComponent->SetOriginalPos(m_OriginalPoint);
	}
}