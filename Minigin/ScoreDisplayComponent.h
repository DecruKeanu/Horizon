#pragma once
#include "Component.h"

namespace Horizon
{
	class TextComponent;
    class ScoreDisplayComponent final : public Component
    {
	public:
		ScoreDisplayComponent(GameObject* parent);
		void Initialize() override;
		void ScoreIncreased(int score) const;
	private:
		TextComponent* m_pParentTextComponent = nullptr;
		std::string m_StartText;
    };
}

