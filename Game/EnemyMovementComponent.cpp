#include "GamePCH.h"
#include "EnemyMovementComponent.h"
#include "EnemyInputComponent.h"
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
m_ElapsedTime{},
m_IsEnemyOnFloor{},
m_TilesEncountered{}
{

}

void EnemyMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<EnemyInputComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void EnemyMovementComponent::Update()
{
	LetEnemyFall();

	if (!m_IsEnemyOnFloor)
		return;

	const Horizon::IPoint2& move = m_pMovementComponent->GetMove();

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	IPoint2 blockOffset = {};

	if (m_IsMovementSideways == false)
		blockOffset = { 32,48 };
	else
	{
		if (move.y == -1)
			blockOffset = { 64,0 };
		else if (move.y == 1)
			blockOffset = { 32,-48 };
	}

	const IPoint2 moveDistance = blockOffset * move;
	const IPoint2 desiredPos = m_OriginalPoint + moveDistance;
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos, m_ElapsedTime);


	if (m_pMovementComponent->GetStepsTaken() < 7)
	{
		m_TilesEncountered = true;
	}
	else if (m_TilesEncountered == false && m_pTriggerComponent->GetOverlappingActorsSize() > 0 && m_ElapsedTime > 0.5f)
	{
		m_TilesEncountered = true;
	}


	const int height = (!m_IsMovementSideways) ? int(moveDistance.y * sinf(m_ElapsedTime * float(M_PI))) : 0;
	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y - height * move.y);

	if (currentPos == desiredPos)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint += moveDistance;

		if (move.x == 0 && move.y == 0)
			return;

		if (m_TilesEncountered == false)
			m_pGameObject->Deactivate();

		m_TilesEncountered = false;
	}
}

void EnemyMovementComponent::LetEnemyFall()
{
	if (m_IsEnemyOnFloor)
		return;

	m_pMovementComponent->DisableMovement();

	const IPoint2 desiredPos = m_FallPoint;

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos, m_ElapsedTime);

	m_pTransformComponent->SetPosition(currentPos);

	if (currentPos.x == desiredPos.x && currentPos.y == desiredPos.y)
	{
		m_pMovementComponent->EnableMovement();
		m_ElapsedTime = 0.f;
		m_OriginalPoint = { desiredPos.x, desiredPos.y };
		m_IsEnemyOnFloor = true;
	}
}
