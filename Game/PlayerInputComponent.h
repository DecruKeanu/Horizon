#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunctionComponent;
	class TriggerComponent;
}

class GameSpriteComponent;
class MovementComponent;


class PlayerInputComponent final : public Horizon::Component
{
public:
	PlayerInputComponent(Horizon::GameObject* parent);
	void ResetInput();
	bool GetCanInputBeRegistered();
	void DeactivateInput();

	const Horizon::IPoint2& GetMove();
private:
	void Initialize() override;
	void Update() override;

	bool m_CanInputBeRegistered;
	Horizon::IPoint2 m_Move;
	
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	MovementComponent* m_pPlayerMovementComponent = nullptr;
	GameSpriteComponent* m_pGameSpriteComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
};

