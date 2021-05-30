#pragma once
#include <vector>
#include <string>
#include <memory>
#include <PrefabFactory.h>

namespace dae
{
	class Prefab;
}

class LevelReader final
{
public:
	LevelReader();
	~LevelReader();
	void ParseLevel(const std::wstring& fileName);
	const std::vector<dae::Prefab*>& GetPrefabs() const;
private:
	std::vector<dae::Prefab*> m_pPrefabs;
	dae::PrefabFactory m_Factory;
};

