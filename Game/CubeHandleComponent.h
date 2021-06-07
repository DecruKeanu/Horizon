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

	//Public helper functions
	void ActivateCube();
	void DeactivateCube();
	void SwitchSprite();

	//Getters
	bool GetisActivated() const;
private:
	//Component functions
	void Initialize() override;

	//Helper functions
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	//Variables
	int m_Level;
	int m_jumps;
	bool m_IsActivated;
};

