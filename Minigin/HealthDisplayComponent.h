#pragma once
#include "Component.h"

namespace Horizon
{
	class TextComponent;
	class HealthDisplayComponent final : public Component
	{
	public:
		HealthDisplayComponent(GameObject* parent,int health);
		void Initialize() override;
		void SetHealthText(int CurrentLives) const;
		void GameOver() const;
	private:
		TextComponent* m_pParentTextComponent = nullptr;
		int m_StartHealth;
	};
}