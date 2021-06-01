#pragma once
#include "Scene.h"

class CubeHandleComponent;

class SoloLevel1Scene final : public Horizon::Scene
{
public:
	SoloLevel1Scene();
private:
	void Initialize() override;
	void Update() override;
	std::vector<CubeHandleComponent*> m_pCubeHandles;
};
