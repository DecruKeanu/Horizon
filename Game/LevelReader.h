#pragma once
#include <vector>
#include <string>
#include <memory>
#include <PrefabFactory.h>

namespace Horizon
{
	class GameObject;
}

class LevelReader final
{
public:
	LevelReader();
	~LevelReader();
	void ParseLevel(const std::wstring& fileName);
	const std::vector<Horizon::GameObject*>& GetPrefabs() const;
private:
	std::vector<Horizon::GameObject*> m_pPrefabs;
	Horizon::PrefabFactory m_Factory;
};

