#pragma once
#include <Component.h>
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class SpriteComponent;
	class TriggerComponent;
}

enum class Input
{
	noInput,
	leftDown = SDLK_s,
	leftUp = SDLK_q,
	rightDown = SDLK_d,
	rightUp = SDLK_z
};


class PlayerInputComponent final : public Horizon::Component
{
public:
	PlayerInputComponent(Horizon::GameObject* parent);
	void ResetInput();
	bool GetCanInputBeRegistered();
	const Horizon::IPoint2& GetMove() const;
private:
	void Initialize() override;
	void Update() override;

	Horizon::IPoint2 m_Move;
	Input m_CurrentInput;

	float m_InputTimer;
	bool m_CanInputBeRegistered;
};

