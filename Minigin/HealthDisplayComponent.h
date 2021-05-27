#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class HealthDisplayComponent final : public Component
	{
	public:
		HealthDisplayComponent(GameObject* parent);
		void Initialize() override;
		void LifeLost(int CurrentLives) const;
		void GameOver() const;
	private:
		TextComponent* m_pParentTextComponent = nullptr;
		std::string m_StartText;
	};
}