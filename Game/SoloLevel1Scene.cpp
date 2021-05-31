#include "GamePCH.h"
#include "SoloLevel1Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Cube.h"
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
	LevelReader levelReader{};
	levelReader.ParseLevel(L"SoloLevel1.json");

	for (Prefab* const pPrefab : levelReader.GetPrefabs())
	{
		if (pPrefab == nullptr)
		{
			Logger::LogWarning("SoloLevel1Scene::Initialize: Prefab was nullptr, skipping element");
			continue;
		}
		Add(pPrefab->GetGameObject());
	}
}
