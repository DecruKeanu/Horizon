#pragma once
#include <vector>
#include <string>
#include <memory>
#include <PrefabFactory.h>

namespace Horizon
{
	class Prefab;
}

class LevelReader final
{
public:
	LevelReader();
	~LevelReader();
	void ParseLevel(const std::wstring& fileName);
	const std::vector<Horizon::Prefab*>& GetPrefabs() const;
private:
	std::vector<Horizon::Prefab*> m_pPrefabs;
	Horizon::PrefabFactory m_Factory;
};

