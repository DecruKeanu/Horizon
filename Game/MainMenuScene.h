#pragma once
#include "Scene.h"

namespace horizon
{
	class TransformObject;
}

class MainMenuScene final : public Horizon::Scene
{
public:
	//Public enum class
	enum class ModeSelected
	{
		singlePlayer,
		Cooperative,
		versus
	};

	MainMenuScene();

private:
	//Scene functions
	void Initialize() override;
	void Update() override;

	//Components
	Horizon::TransformComponent* m_pArrowTransformComponent = nullptr;

	//Variables
	ModeSelected m_CurrentModeSelected;

	bool m_InputPressed;
};

