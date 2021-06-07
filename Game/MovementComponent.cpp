#include "GamePCH.h"
#include "MovementComponent.h"

#include <SpriteComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>

#include <Timer.h>

MovementComponent::MovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways) : Component(pParent),
m_FallPoint{ fallPoint },
m_IsMovementSideways{ IsMovementSideways },
m_OriginalPoint{},
m_Move{},
m_ElapsedTime{},
m_IsCharacterOnFloor{}
{

}

void MovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void MovementComponent::Update()
{
	CharacterFalling();

	if (!m_IsCharacterOnFloor)
		return;

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Horizon::Timer::GetInstance().GetDeltaTime());

	//Calculates the blockOffset when Escheresque movement is wanted, if Escheresque movement is not wanted use normal blockOffset
	const Horizon::IPoint2 blockOffset = (m_IsMovementSideways && m_Move.y == -1) ? Horizon::IPoint2{ 64, 0 } : (m_IsMovementSideways && m_Move.y == 1) ? Horizon::IPoint2{ 32,-48 } : Horizon::IPoint2{ 32,48 };

	const Horizon::IPoint2 moveDistance = blockOffset * m_Move;
	const Horizon::IPoint2 desiredPos = m_OriginalPoint + moveDistance;
	const Horizon::IPoint2 currentPos = Horizon::MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos, m_ElapsedTime);

	//Only hop when movement is not sideways
	const int hopHeight = (!m_IsMovementSideways) ? int(moveDistance.y * sinf(m_ElapsedTime * float(M_PI))) : 0;
	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y - hopHeight * m_Move.y);



	if (currentPos == desiredPos)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint += moveDistance;

		m_Move = { 0,0 };
	}
}

void MovementComponent::CharacterFalling()
{
	if (m_IsCharacterOnFloor)
		return;

	m_ElapsedTime += Horizon::Timer::GetInstance().GetDeltaTime();
	const bool lerpedPosReached = HelperFunctions::MoveToLerpedPos(m_OriginalPoint, m_FallPoint, m_ElapsedTime, m_pTransformComponent);

	if (lerpedPosReached)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = m_FallPoint;
		m_IsCharacterOnFloor = true;
	}
}

void MovementComponent::SetMove(const Horizon::IPoint2& input)
{
	m_Move = input;
}

void MovementComponent::SetOriginalPos(const Horizon::IPoint2& input)
{
	m_OriginalPoint = input;
}

const Horizon::IPoint2& MovementComponent::GetOriginalPos() const
{
	return m_OriginalPoint;
}