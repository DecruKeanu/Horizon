#include "GamePCH.h"
#include "PlayerMovementComponent.h"
#include "PlayerInputComponent.h"
#include "SpriteComponent.h"
#include <TriggerComponent.h>
#include "InputManager.h"
#include "GameCommands.h"
#include "Timer.h"
#include <SceneManager.h>
#include <GameObject.h>
#include <MathHelper.h>

using namespace Horizon;

PlayerMovementComponent::PlayerMovementComponent(GameObject* parent) : Component(parent),
m_OriginalPoint{},
m_ElapsedTime{},
m_IsPlayerOnFlyingDisc{},
m_IsFallingOfFlyingDisc{}
{
}

void PlayerMovementComponent::PlayerOnFlyingDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent)
{
	m_pFlyingDiscTransformComponent = pFlyingDiscTransformComponent;
	m_IsPlayerOnFlyingDisc = true;
}

void PlayerMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<PlayerInputComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void PlayerMovementComponent::Update()
{
	PlayerOnFlyingDisc();
	FallingOfFlyingDisc();

	if (m_IsPlayerOnFlyingDisc || m_IsFallingOfFlyingDisc)
		return;

	const Horizon::IPoint2& move = m_pMovementComponent->GetMove();
	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	const IPoint2 blockOffset = { 32, 48 };
	const IPoint2 moveDistance = { blockOffset.x * move.x,blockOffset.y * move.y };
	const IPoint2 desiredPos{ m_OriginalPoint.x + moveDistance.x, m_OriginalPoint.y + moveDistance.y };
	const IPoint2 currentPos = MathHelper::IPoint2Lerp(m_OriginalPoint, desiredPos,m_ElapsedTime);

	const int height = int(moveDistance.y * sinf(m_ElapsedTime * float(M_PI)));
	m_pTransformComponent->SetPosition(currentPos.x, currentPos.y - height * move.y, 0);

	if (currentPos.x == desiredPos.x && currentPos.y == desiredPos.y)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint.x += moveDistance.x;
		m_OriginalPoint.y += moveDistance.y;

		if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
			Logger::LogInfo("Player is in the void");
	}
}

void PlayerMovementComponent::PlayerOnFlyingDisc()
{
	if (!m_IsPlayerOnFlyingDisc)
		return;

	const IPoint2 playerOffset = { 2,-22 };
	const IPoint2 desiredPos = { 310 + playerOffset.x,32 + playerOffset.y };

	if (m_pTransformComponent->GetPosition().x != desiredPos.x && m_pTransformComponent->GetPosition().y != desiredPos.y)
		m_pTransformComponent->SetPosition(m_pFlyingDiscTransformComponent->GetPosition().x + playerOffset.x, m_pFlyingDiscTransformComponent->GetPosition().y + playerOffset.y, m_pFlyingDiscTransformComponent->GetPosition().z);
	else
	{
		m_ElapsedTime = 0.f;
		m_IsFallingOfFlyingDisc = true;
		m_IsPlayerOnFlyingDisc = false;
		m_OriginalPoint = desiredPos;
	}
}

void PlayerMovementComponent::FallingOfFlyingDisc()
{
	if (!m_IsFallingOfFlyingDisc)
		return;

	const IPoint2 desiredPos = { 307,57 };

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());
	const int xPos = MathHelper::ILerp(m_OriginalPoint.x, desiredPos.x, m_ElapsedTime);
	const int yPos = MathHelper::ILerp(m_OriginalPoint.y, desiredPos.y, m_ElapsedTime);

	m_pTransformComponent->SetPosition(xPos, yPos, m_pFlyingDiscTransformComponent->GetPosition().z);

	if (xPos == desiredPos.x && yPos == desiredPos.y)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint = { desiredPos.x, desiredPos.y };
		m_IsFallingOfFlyingDisc = false;
	}
}

