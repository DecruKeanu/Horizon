#include "GamePCH.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include <TriggerComponent.h>
#include "InputManager.h"
#include "GameCommands.h"
#include "Timer.h"
#include <SceneManager.h>
#include <GameObject.h>

using namespace Horizon;

MovementComponent::MovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways) : Component(pParent),
	m_FallPoint{fallPoint},
	m_IsMovementSideways{IsMovementSideways},
	m_PreviousPoint{},
	m_OriginalPoint{},
	m_Move{},
	m_StepsTaken{},
	m_ElapsedTime{},
	m_IsCharacterOnFloor{},
	m_TilesEncountered{}
{

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

void MovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void MovementComponent::Update()
{
	LetCharacterFall();

	if (!m_IsCharacterOnFloor|| (m_Move.x == 0 && m_Move.y == 0))
		return;

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	IPoint2 blockOffset = {};

	if (m_IsMovementSideways == false)
		blockOffset = { 32,48 };
	else
	{
		//Calculates the blockoffset when Escheresque movement is wanted
		blockOffset = (m_Move.y == -1) ? Horizon::IPoint2{ 64, 0 } : (m_Move.y == 1) ? Horizon::IPoint2{ 32,-48 } : Horizon::IPoint2{};
	}


	const IPoint2 moveDistance = blockOffset * m_Move;
	const IPoint2 desiredPos = m_OriginalPoint + moveDistance;
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos, m_ElapsedTime);

	const int height = (!m_IsMovementSideways) ? int(moveDistance.y * sinf(m_ElapsedTime * float(M_PI))) : 0;
	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y - height * m_Move.y);

	if (currentPos.x == desiredPos.x && currentPos.y == desiredPos.y)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint += moveDistance;

		m_Move = { 0,0 };
	}
}

void MovementComponent::LetCharacterFall()
{
	if (m_IsCharacterOnFloor)
		return;

	const IPoint2 desiredPos = m_FallPoint;

	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();

	if (HelperFunctions::MoveToLerpedPos(m_OriginalPoint, m_FallPoint, m_ElapsedTime, m_pTransformComponent))
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = m_FallPoint;
		m_IsCharacterOnFloor = true;
	}
}

