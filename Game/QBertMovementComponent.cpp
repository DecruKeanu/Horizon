#include "GamePCH.h"
#include "QBertMovementComponent.h"
#include "InputManager.h"
#include "GameCommands.h"
#include "Logger.h"
#include <cmath>
#include "Timer.h"

using namespace dae;

QBertMovementComponent::QBertMovementComponent(dae::GameObject* parent) : Component(parent),
m_CurrentMovement{ Movement::idle },
m_OriginalPoint{},
m_ElapsedTime{},
m_CanInputBeRegistered{ true }
{
}

void QBertMovementComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();

	if (m_pTransformComponent == nullptr)
	{
		Logger::LogWarning("QBertMovementComponent::Initialize >> QBert does not have transformComponent");
		return;
	}

	m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_z, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(this));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_q, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(this));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_s, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(this));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_d, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(this));
}

void QBertMovementComponent::Update()
{
	float movementTime = 1.f;
	IPoint2 movementPos{};

	switch (m_CurrentMovement)
	{
	case Movement::idle:
		return;
	case Movement::leftDown:
		movementPos = { m_OriginalPoint.x - 32,m_OriginalPoint.y + 48 };
		m_CanInputBeRegistered = false;
		break;
	case Movement::leftUp:
		movementPos = { m_OriginalPoint.x - 32,m_OriginalPoint.y - 48 };
		m_CanInputBeRegistered = false;
		break;
	case Movement::rightDown:
		movementPos = { m_OriginalPoint.x + 32,m_OriginalPoint.y + 48 };
		m_CanInputBeRegistered = false;
		break;
	case Movement::rightUp:
		movementPos = { m_OriginalPoint.x + 32,m_OriginalPoint.y - 48 };
		m_CanInputBeRegistered = false;
		break;
	}


	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();

	const int xPos = int(m_OriginalPoint.x + (movementPos.x - m_OriginalPoint.x) * m_ElapsedTime);
	const int yPos = int(m_OriginalPoint.y + (movementPos.y - m_OriginalPoint.y) * m_ElapsedTime);

	m_pTransformComponent->SetPosition(xPos, yPos, 0);

	if (m_ElapsedTime >= movementTime)
	{
		m_ElapsedTime = 0.f;
		m_CanInputBeRegistered = true;
		m_OriginalPoint = { m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y };
		m_CurrentMovement = Movement::idle;
	}
}

void QBertMovementComponent::SetCurrentMovement(Movement movement)
{
	if (m_CanInputBeRegistered == true)
		m_CurrentMovement = movement;
}