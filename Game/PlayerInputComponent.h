#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunction;
}

class PlayerInputComponent final : public Horizon::Component
{
public:
	PlayerInputComponent(Horizon::GameObject* parent);
	~PlayerInputComponent();
	void ResetInput();
	bool GetCanInputBeRegistered();
	void DeactivateInput();

	const Horizon::IPoint2& GetMove();
private:
	void Initialize() override;
	void Update() override;

	bool m_CanInputBeRegistered;
	Horizon::IPoint2 m_Move;
	Horizon::TimedFunction* m_pTimedFunction = nullptr;
};

