#pragma once
#include "Component.h"
namespace dae
{
	class GameObject;
	class TransformComponent;
}

enum class Movement
{
	idle,
	leftDown,
	leftUp,
	rightDown,
	rightUp
};

class QBertMovementComponent final : public dae::Component
{
public:
	QBertMovementComponent(dae::GameObject* parent);

	void SetCurrentMovement(Movement movement);


private:
	void Initialize() override;
	void Update() override;

	bool m_CanInputBeRegistered;
	float m_ElapsedTime;
	IPoint2 m_OriginalPoint;
	Movement m_CurrentMovement;
	dae::TransformComponent* m_pTransformComponent = nullptr;
};

