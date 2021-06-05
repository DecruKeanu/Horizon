#include "GamePCH.h"
#include "EnemyMovementComponent.h"
#include "EnemyInputComponent.h"
#include "CoilyInputComponent.h"
#include "SpriteComponent.h"
#include <TriggerComponent.h>
#include "InputManager.h"
#include "GameCommands.h"
#include "Timer.h"
#include <SceneManager.h>
#include <GameObject.h>

using namespace Horizon;

EnemyMovementComponent::EnemyMovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways) : Component(pParent),
m_FallPoint{ fallPoint },
m_IsMovementSideways{ IsMovementSideways },
m_OriginalPoint{},
m_Move{},
m_StepsTaken{},
m_ElapsedTime{},
m_IsEnemyOnFloor{},
m_TilesEncountered{}
{

}


void EnemyMovementComponent::SetMove(const Horizon::IPoint2& input)
{
	m_Move = input;
}

void EnemyMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void EnemyMovementComponent::Update()
{
	LetEnemyFall();

	if (!m_IsEnemyOnFloor)
		return;

	//const Horizon::IPoint2& move = m_pMovementComponent->GetMove();

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	IPoint2 blockOffset = {};

	if (m_IsMovementSideways == false)
		blockOffset = { 32,48 };
	else
	{
		//Calculates the blockoffset when Escheresque movement is wanted
		blockOffset = (m_Move.y == -1) ? Horizon::IPoint2{ 64, 0 } : (m_Move.y == 1) ? Horizon::IPoint2{ 32,-48 } : Horizon::IPoint2{};
	}

	if (m_StepsTaken < 7)
	{
		m_TilesEncountered = true;
	}
	else if (m_TilesEncountered == false && m_pTriggerComponent->GetOverlappingActorsSize() > 0 && m_ElapsedTime > 0.5f)
	{
		m_TilesEncountered = true;
	}

	const IPoint2 moveDistance = blockOffset * m_Move;
	const IPoint2 desiredPos = m_OriginalPoint + moveDistance;
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos, m_ElapsedTime);

	const int height = (!m_IsMovementSideways) ? int(moveDistance.y * sinf(m_ElapsedTime * float(M_PI))) : 0;
	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y - height * m_Move.y);

	if (currentPos == desiredPos)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint += moveDistance;

		if (m_Move.x == 0 && m_Move.y == 0)
			return;

		m_StepsTaken++;
		if (m_TilesEncountered == false)
			m_pGameObject->Deactivate();

		m_TilesEncountered = false;
	}
}

void EnemyMovementComponent::LetEnemyFall()
{
	if (m_IsEnemyOnFloor)
		return;

	const IPoint2 desiredPos = m_FallPoint;

	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();

	if (HelperFunctions::MoveToLerpedPos(m_OriginalPoint, m_FallPoint, m_ElapsedTime, m_pTransformComponent))
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = m_FallPoint;
		m_IsEnemyOnFloor = true;
	}
}
