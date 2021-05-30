#pragma once
#include "Command.h"
#include "QBertMovementComponent.h"

class MoveDownCommand final : public Command
{
public:
	MoveDownCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::leftDown); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveUpCommand final : public Command
{
public:
	MoveUpCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::rightUp); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveLeftCommand final : public Command
{
public:
	MoveLeftCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::leftUp); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveRightCommand final : public Command
{
public:
	MoveRightCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::rightDown); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};


