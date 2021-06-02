#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class SpriteComponent;
}

enum class CubeType
{
	oneJump,
	twoJumps,
	loopjumps
};


class CubeHandleComponent final : public Horizon::Component
{
public:
	CubeHandleComponent(Horizon::GameObject* parent, const CubeType& cubeType);
	void ActivateCube();
	bool GetisActivated() const;
private:
	void Initialize() override;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	CubeType m_CubeType;
	int m_jumps;
	bool m_IsActivated;

};

