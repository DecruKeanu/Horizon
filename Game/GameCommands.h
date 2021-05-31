#pragma once
#include "Command.h"
#include "QBertMovementComponent.h"

class MoveDownCommand final : public Horizon::Command
{
public:
	MoveDownCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::leftDown); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveUpCommand final : public Horizon::Command
{
public:
	MoveUpCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::rightUp); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveLeftCommand final : public Horizon::Command
{
public:
	MoveLeftCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::leftUp); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};

class MoveRightCommand final : public Horizon::Command
{
public:
	MoveRightCommand(QBertMovementComponent* pMovementComponent) : m_pMovementComponent{ pMovementComponent } {}
	void Execute() override { m_pMovementComponent->SetCurrentMovement(Movement::rightDown); }
	QBertMovementComponent* m_pMovementComponent = nullptr;
};


