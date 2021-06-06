#pragma once
#include "Scene.h"

namespace horizon
{
	class TransformObject;
}

class MainMenuScene final : public Horizon::Scene
{
public:
	enum class ModeSelected
	{
		singlePlayer,
		Cooperative,
		versus
	};

	MainMenuScene();
	void Initialize() override;
	void Update() override;
private:
	Horizon::TransformComponent* m_pArrowTransformComponent = nullptr;
	ModeSelected m_CurrentModeSelected;

	bool m_InputPressed;
};

