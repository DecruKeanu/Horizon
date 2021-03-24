#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class TextComponent;
	class HealthDisplayComponent final : public ObjectComponent
	{
	public:
		HealthDisplayComponent(GameObject* parent);
		void BeginPlay() override;
		void LifeLost(int CurrentLives) const;
		void GameOver() const;
	private:
		TextComponent* m_pParentTextComponent = nullptr;
		std::string m_StartText;
	};
}