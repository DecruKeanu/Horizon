#pragma once
#include "Component.h"
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class SpriteComponent;
	class TriggerComponent;
}
class QBertInputComponent;

class QBertMovementComponent final : public Horizon::Component
{
public:
	QBertMovementComponent(Horizon::GameObject* parent);
private:
	void Initialize() override;
	void Update() override;

	float m_ElapsedTime;
	Horizon::IPoint2 m_OriginalPoint;

	QBertInputComponent* m_pQBertInputComponent = nullptr;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

