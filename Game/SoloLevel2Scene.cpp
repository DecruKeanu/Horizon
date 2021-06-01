#include "GamePCH.h"
#include "SoloLevel2Scene.h"
#include "LevelReader.h"

using namespace Horizon;

SoloLevel2Scene::SoloLevel2Scene() : Scene("SoloLevel2Scene")
{

}

void SoloLevel2Scene::Initialize()
{
	LevelReader levelReader{};
	levelReader.ParseLevel(L"SoloLevel2.json");

	for (GameObject* const pPrefab : levelReader.GetPrefabs())
	{
		Add(pPrefab);
	}
}
