#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
}

class FlyingDiscMovementComponent final : public Horizon::Component
{
public:
	FlyingDiscMovementComponent(Horizon::GameObject* pParent);
private:
	void Initialize();
};

