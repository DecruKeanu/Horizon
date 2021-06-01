#include "GamePCH.h"
#include "SoloLevel1Scene.h"
#include "LevelReader.h"
#include "CubeHandleComponent.h"
using namespace Horizon;

SoloLevel1Scene::SoloLevel1Scene() : Scene("SoloLevel1Scene"),
	m_pCubeHandles{}
{

}

void SoloLevel1Scene::Initialize()
{
	LevelReader levelReader{};
	levelReader.ParseLevel(L"SoloLevel1.json");

	for (GameObject* const pPrefab : levelReader.GetPrefabs())
	{
		Add(pPrefab);
	}

	std::vector<GameObject*> pCubes = GetGameObjects("Cube");

	for (GameObject* const pCube : pCubes)
		m_pCubeHandles.push_back(pCube->GetComponent<CubeHandleComponent>());
}

void SoloLevel1Scene::Update()
{
	//for (CubeHandleComponent* const pCubeHandle : m_pCubeHandles)
	//{
	//	if (!pCubeHandle->GetisActivated())
	//		return;
	//}
	//SceneManager::GetInstance().NextScene();

	//for (CubeHandleComponent* const pCubeHandle : m_pCubeHandles)
	//{
	//	if (pCubeHandle->GetisActivated())
	//		SceneManager::GetInstance().NextScene();
	//}

}
