#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}

class CubeHandleComponent final : public Horizon::Component
{
public:
	CubeHandleComponent(Horizon::GameObject* parent, int level);
	void ActivateCube();
	bool GetisActivated() const;
	void SwitchSprite();
private:
	void Initialize() override;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	int m_Level;
	int m_jumps;
	bool m_IsActivated;
};

