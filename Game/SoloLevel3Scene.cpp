#include "GamePCH.h"
#include "SoloLevel3Scene.h"
#include "LevelReader.h"

using namespace Horizon;

SoloLevel3Scene::SoloLevel3Scene() : Scene("SoloLevel3Scene")
{

}

void SoloLevel3Scene::Initialize()
{
	LevelReader levelReader{};
	levelReader.ParseLevel(L"SoloLevel3.json");

	for (GameObject* const pPrefab : levelReader.GetPrefabs())
	{
		Add(pPrefab);
	}
}
