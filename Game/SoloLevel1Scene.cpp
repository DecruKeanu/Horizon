#include "GamePCH.h"
#include "SoloLevel1Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Cube.h"
#include "QBert.h"
#include "QBertMovementComponent.h"
#include "CubeHandleObserver.h"
#include "CubeHandleComponent.h"
#include "LevelReader.h"
#include "InputManager.h"
#include "Command.h"
#include <memory>
#include <vld.h>

using namespace Horizon;

SoloLevel1Scene::SoloLevel1Scene() : Scene("SoloLevel1Scene")
{

}

void SoloLevel1Scene::Initialize()
{
	std::vector<Cube*> pCubePrefabs{};
	LevelReader levelReader{};
	levelReader.ParseLevel(L"SoloLevel1.json");

	for (Prefab* const pPrefab : levelReader.GetPrefabs())
	{
		if (pPrefab == nullptr)
		{
			Logger::LogWarning("SoloLevel1Scene::Initialize: Prefab was nullptr, skipping element");
			continue;
		}

		if (pPrefab->GetPrefabName() == "Cube")
			pCubePrefabs.push_back(static_cast<Cube*>(pPrefab));
		else if (pPrefab->GetPrefabName() == "QBert")
		{
			QBert* const pQbert = static_cast<QBert*>(pPrefab);
			for (Cube* const pCubeElement : pCubePrefabs)
			{
				pQbert->GetGameObject()->GetComponent<QBertMovementComponent>()->AddObserver(new CubeHandleObserver(pCubeElement->GetGameObject()->GetComponent<CubeHandleComponent>()));
			}
		}

		Add(pPrefab->GetGameObject());
	}
}
