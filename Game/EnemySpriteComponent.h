#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}

class EnemyInputComponent;


class EnemySpriteComponent final : public Horizon::Component
{
public:
	EnemySpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect);
private:
	void Initialize() override;
	void Update() override;

	int m_CurrentSpriteNumber;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
	EnemyInputComponent* m_pInputComponent = nullptr;
};

