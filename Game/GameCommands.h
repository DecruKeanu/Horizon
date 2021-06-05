#pragma once
#include "Command.h"
#include "MovementComponent.h"

class MoveUpCommand final : public Horizon::Command
{
public:
	MoveUpCommand(Horizon::IPoint2& move, const bool& canInputBeRegisted) : m_Move{ move }, m_CanInputBeRegistered{ canInputBeRegisted } {}
	void Execute() override
	{
		if (m_CanInputBeRegistered)
		{
			m_Move.x = -1;
			m_Move.y = -1;
		}
	}

	Horizon::IPoint2& m_Move;
	const bool& m_CanInputBeRegistered;
};

class MoveDownCommand final : public Horizon::Command
{
public:
	MoveDownCommand(Horizon::IPoint2& move, const bool& canInputBeRegisted) : m_Move{ move }, m_CanInputBeRegistered{ canInputBeRegisted } {}
	void Execute() override
	{ 
		if (m_CanInputBeRegistered)
		{
			m_Move.x = 1;
			m_Move.y = 1;
		}
	}

	Horizon::IPoint2& m_Move;
	const bool& m_CanInputBeRegistered;
};


class MoveLeftCommand final : public Horizon::Command
{
public:
	MoveLeftCommand(Horizon::IPoint2& move, const bool& canInputBeRegisted) : m_Move{ move }, m_CanInputBeRegistered{ canInputBeRegisted } {}
	void Execute() override
	{
		if (m_CanInputBeRegistered)
		{
			m_Move.x = -1;
			m_Move.y = 1;
		}
	}

	Horizon::IPoint2& m_Move;
	const bool& m_CanInputBeRegistered;
};

class MoveRightCommand final : public Horizon::Command
{
public:
	MoveRightCommand(Horizon::IPoint2& move, const bool& canInputBeRegisted) : m_Move{ move }, m_CanInputBeRegistered{ canInputBeRegisted } {}
	void Execute() override
	{
		if (m_CanInputBeRegistered)
		{
			m_Move.x = 1;
			m_Move.y = -1;
		}
	}

	Horizon::IPoint2& m_Move;
	const bool& m_CanInputBeRegistered;
};


