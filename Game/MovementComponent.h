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

	void SetMove(const Horizon::IPoint2& input);
	void SetOriginalPos(const Horizon::IPoint2& input);

	const Horizon::IPoint2& GetOriginalPos() const;
private:
	void Initialize() override;
	void Update() override;
	void LetCharacterFall();

	int m_StepsTaken;
	bool m_IsMovementSideways;
	bool m_IsCharacterOnFloor;
	bool m_TilesEncountered;
	float m_ElapsedTime;

	Horizon::IPoint2 m_FallPoint;
	Horizon::IPoint2 m_Move;
	Horizon::IPoint2 m_PreviousPoint;
	Horizon::IPoint2 m_OriginalPoint;

	Horizon::IPoint2 m_BlockOffset;

	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

