#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class TextComponent;
    class ScoreDisplayComponent final : public ObjectComponent
    {
	public:
		ScoreDisplayComponent(GameObject* parent);
		void BeginPlay();
		void ScoreIncreased(int score) const;
	private:
		TextComponent* m_pParentTextComponent = nullptr;
		std::string m_StartText;
    };
}

