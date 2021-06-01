#pragma once
#include "Component.h"
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class SpriteComponent;
}

enum class Movement
{
	idle,
	leftDown,
	leftUp,
	rightDown,
	rightUp
};

class QBertMovementComponent final : public Horizon::Component
{
public:
	QBertMovementComponent(Horizon::GameObject* parent);
	~QBertMovementComponent();
	void SetCurrentMovement(Movement movement);
private:
	void Initialize() override;
	void Update() override;

	bool m_CanInputBeRegistered;
	float m_ElapsedTime;
	Horizon::IPoint2 m_OriginalPoint;
	Movement m_CurrentMovement;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	std::vector<Horizon::GameObject*> m_pCubes;
};

