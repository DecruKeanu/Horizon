#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;
	class FPS final : public Component
	{
	public:
		FPS(GameObject* parent);
		void Initialize() override;
		void Update() override;
	private:
		TextComponent* m_pTextComponent = nullptr;
	};
}