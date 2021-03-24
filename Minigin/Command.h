#pragma once
#include "HealthComponent.h"
#include "ScoreComponent.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class LifeLostCommand final : public Command
{
public:
	LifeLostCommand(dae::HealthComponent* health) : m_pHealth{ health } {}
	void Execute() override { m_pHealth->DecreaseLive(); }
	dae::HealthComponent* m_pHealth = nullptr;
};

class ColorChangeCommand final : public Command
{
public:
	ColorChangeCommand(dae::ScoreComponent* score) : m_pScore{ score } {}
	void Execute() override { m_pScore->IncreaseScore(25); }
	dae::ScoreComponent* m_pScore = nullptr;
};

class RemainingDiscCommand final : public Command
{
public:
	RemainingDiscCommand(dae::ScoreComponent* score) : m_pScore{ score } {}
	void Execute() override { m_pScore->IncreaseScore(50); }
	dae::ScoreComponent* m_pScore = nullptr;
};

class CatchingSamOrSlickCommand final : public Command
{
public:
	CatchingSamOrSlickCommand(dae::ScoreComponent* score) : m_pScore{ score } {}
	void Execute() override { m_pScore->IncreaseScore(300); }
	dae::ScoreComponent* m_pScore = nullptr;
};

class DefeatCoilyCommand final : public Command
{
public:
	DefeatCoilyCommand(dae::ScoreComponent* score) : m_pScore{ score } {}
	void Execute() override { m_pScore->IncreaseScore(500); }
	dae::ScoreComponent* m_pScore = nullptr;
};
