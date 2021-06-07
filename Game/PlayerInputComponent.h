#pragma once
#include <Component.h>

class MovementComponent;
class GameSpriteComponent;

namespace Horizon
{
	class GameObject;
	class TimedFunctionComponent;
	class TriggerComponent;
}

class PlayerInputComponent final : public Horizon::Component
{
public:
	PlayerInputComponent(Horizon::GameObject* parent, bool isFirstPlayer);

	//Public helper functions
	void ActivateInput();
	void DeactivateInput();

	//Getters
	bool GetCanInputBeRegistered() const;
	const Horizon::IPoint2& GetMove() const;
private:
	//Component functions
	void Initialize() override;
	void Update() override;

	//Helper functions
	void InitializeInput();
	void InitializeInputTimedFunction();
	void InitializeStartInputTimedFunction();

	//Components
	GameSpriteComponent* m_pGameSpriteComponent = nullptr;
	MovementComponent* m_pPlayerMovementComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pInputTimedFunction = nullptr;

	//Variables
	bool m_IsFirstPlayer;
	bool m_CanInputBeRegistered;
	Horizon::IPoint2 m_Move;
};

