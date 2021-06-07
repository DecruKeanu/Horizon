#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include <TransformComponent.h>
#include "MainMenuScene.h"

class InputPressedCommand final : public Horizon::Command
{
public:
	InputPressedCommand(bool& inputPressed) :m_InputPressed{ inputPressed } {}
	void Execute() override
	{
		m_InputPressed = true;
	}

	bool& m_InputPressed;
};

class ArrowUpCommand final : public Horizon::Command
{
public:
	ArrowUpCommand(MainMenuScene::ModeSelected& currentMode, Horizon::TransformComponent* pArrowTransform) :m_CurrentModeSelected{ currentMode }, m_pArrowTransformComponent { pArrowTransform } {}
	void Execute() override
	{
		const Horizon::IPoint2 pos = m_pArrowTransformComponent->GetPosition();
		switch (m_CurrentModeSelected)
		{
		case MainMenuScene::ModeSelected::singlePlayer:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y + 160);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::versus;
			break;
		case MainMenuScene::ModeSelected::Cooperative:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y -80);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::singlePlayer;
			break;
		case MainMenuScene::ModeSelected::versus:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y - 80);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::Cooperative;
		}


	}

	MainMenuScene::ModeSelected& m_CurrentModeSelected;
	Horizon::TransformComponent* m_pArrowTransformComponent = nullptr;
};

class ArrowDownCommand final : public Horizon::Command
{
public:
	ArrowDownCommand(MainMenuScene::ModeSelected& currentMode, Horizon::TransformComponent* pArrowTransform) :m_CurrentModeSelected{ currentMode }, m_pArrowTransformComponent{ pArrowTransform } {}
	void Execute() override
	{
		const Horizon::IPoint2 pos = m_pArrowTransformComponent->GetPosition();
		switch (m_CurrentModeSelected)
		{
		case MainMenuScene::ModeSelected::singlePlayer:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y + 80);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::Cooperative;
			break;
		case MainMenuScene::ModeSelected::Cooperative:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y + 80);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::versus;
			break;
		case MainMenuScene::ModeSelected::versus:
			m_pArrowTransformComponent->SetPosition(pos.x, pos.y - 160);
			m_CurrentModeSelected = MainMenuScene::ModeSelected::singlePlayer;
		}
	}

	MainMenuScene::ModeSelected& m_CurrentModeSelected;
	Horizon::TransformComponent* m_pArrowTransformComponent = nullptr;
};

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


