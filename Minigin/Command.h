#pragma once
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TransformComponent.h"

namespace Horizon
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class TestCommand final : public Command
	{
	public:
		TestCommand() = default;
		void Execute() override { std::cout << "TEST\n"; }
	};

	class LifeLostCommand final : public Command
	{
	public:
		LifeLostCommand(HealthComponent* health) : m_pHealth{ health } {}
		void Execute() override { m_pHealth->DecreaseLive(); }
		HealthComponent* m_pHealth = nullptr;
	};

	class ColorChangeCommand final : public Command
	{
	public:
		ColorChangeCommand(ScoreComponent* score) : m_pScore{ score } {}
		void Execute() override { m_pScore->IncreaseScore(25); }
		ScoreComponent* m_pScore = nullptr;
	};

	class RemainingDiscCommand final : public Command
	{
	public:
		RemainingDiscCommand(ScoreComponent* score) : m_pScore{ score } {}
		void Execute() override { m_pScore->IncreaseScore(50); }
		ScoreComponent* m_pScore = nullptr;
	};

	class CatchingSamOrSlickCommand final : public Command
	{
	public:
		CatchingSamOrSlickCommand(ScoreComponent* score) : m_pScore{ score } {}
		void Execute() override { m_pScore->IncreaseScore(300); }
		ScoreComponent* m_pScore = nullptr;
	};

	class DefeatCoilyCommand final : public Command
	{
	public:
		DefeatCoilyCommand(ScoreComponent* score) : m_pScore{ score } {}
		void Execute() override { m_pScore->IncreaseScore(500); }
		ScoreComponent* m_pScore = nullptr;
	};
}

