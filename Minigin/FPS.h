#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class TextComponent;
	class FPS final : public ObjectComponent
	{
	public:
		FPS(GameObject* parent);
		void BeginPlay() override;
		void Update() override;
	private:
		TextComponent* m_pTextComponent = nullptr;
	};
}