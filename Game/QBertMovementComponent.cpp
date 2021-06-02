#include "GamePCH.h"
#include "QBertMovementComponent.h"
#include "QBertInputComponent.h"
#include "SpriteComponent.h"
#include <TriggerComponent.h>
#include "InputManager.h"
#include "GameCommands.h"
#include "Timer.h"
#include <SceneManager.h>
#include <GameObject.h>
#include <MathHelper.h>
using namespace Horizon;

QBertMovementComponent::QBertMovementComponent(GameObject* parent) : Component(parent),
m_OriginalPoint{},
m_ElapsedTime{}
{
}

void QBertMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<SpriteComponent>();
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();
	m_pQBertInputComponent = m_pGameObject->GetComponent<QBertInputComponent>();

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
}

void QBertMovementComponent::Update()
{
	if (m_pQBertInputComponent->GetCanInputBeRegistered())
		return;

	const IPoint2& move = m_pQBertInputComponent->GetMove();

	if (move.x == -1 && move.y == -1)
		m_pSpriteComponent->SetCurrentSprite(3);
	else if (move.x == -1 && move.y == 1)
		m_pSpriteComponent->SetCurrentSprite(7);
	else if (move.x == 1 && move.y == 1)
		m_pSpriteComponent->SetCurrentSprite(5);
	else if (move.x == 1 && move.y == -1)
		m_pSpriteComponent->SetCurrentSprite(1);

	const IPoint2 blockOffset = { 32, 48 };
	const IPoint2 Direction = { blockOffset.x * move.x,blockOffset.y * move.y };

	m_ElapsedTime = std::min(1.f, m_ElapsedTime + Timer::GetInstance().GetDeltaTime());

	const int xPos = int(m_OriginalPoint.x + Direction.x * m_ElapsedTime);
	const int yPos = int(m_OriginalPoint.y + Direction.y * m_ElapsedTime);
	m_pTransformComponent->SetPosition(xPos, yPos, 0);

	if (xPos == m_OriginalPoint.x + Direction.x && yPos == m_OriginalPoint.y + Direction.y)
	{
		m_ElapsedTime = 0.f;
		m_OriginalPoint.x += Direction.x;
		m_OriginalPoint.y += Direction.y;
		m_pQBertInputComponent->ResetInput();
		m_pSpriteComponent->PreviousSprite();

		if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
			Logger::LogInfo("Qbert is in the void");
	}
}

