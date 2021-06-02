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

using namespace Horizon;

PlayerMovementComponent::PlayerMovementComponent(GameObject* parent) : Component(parent),
m_OriginalPoint{},
m_ElapsedTime{}
{
}

void PlayerMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();
	m_pQBertInputComponent = m_pGameObject->GetComponent<PlayerInputComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void PlayerMovementComponent::Update()
{
	if (m_pQBertInputComponent->GetCanInputBeRegistered())
		return;

	const Horizon::IPoint2& move = m_pQBertInputComponent->GetMove();

	const IPoint2 blockOffset = { 32, 48 };
	const IPoint2 direction = { blockOffset.x * move.x,blockOffset.y * move.y };

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	const int xPos = int(m_OriginalPoint.x + direction.x * m_ElapsedTime);
	const int yPos = int(m_OriginalPoint.y + direction.y * m_ElapsedTime);
	m_pTransformComponent->SetPosition(xPos, yPos, 0);

	if (xPos == m_OriginalPoint.x + direction.x && yPos == m_OriginalPoint.y + direction.y)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint.x += direction.x;
		m_OriginalPoint.y += direction.y;
		m_pQBertInputComponent->ResetInput();

		if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
			Logger::LogInfo("Player is in the void");
	}
}

