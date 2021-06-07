#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
}

class MovementComponent final : public Horizon::Component
{
public:
	MovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways);

	//Setters
	void SetMove(const Horizon::IPoint2& input);
	void SetOriginalPos(const Horizon::IPoint2& input);

	//Getters
	const Horizon::IPoint2& GetOriginalPos() const;
private:
	//Component functions
	void Initialize() override;
	void Update() override;

	//Helper functions
	void CharacterFalling();

	//Components
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_Move;
	Horizon::IPoint2 m_FallPoint;
	Horizon::IPoint2 m_OriginalPoint;

	float m_ElapsedTime;
	bool m_IsMovementSideways;
	bool m_IsCharacterOnFloor;
};

