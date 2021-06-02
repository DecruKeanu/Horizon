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
	void ParseLevel(const std::wstring& fileName);
	const std::vector<Horizon::GameObject*>& GetGameObjects() const;
private:
	std::vector<Horizon::GameObject*> m_pGameObjects;
	Horizon::PrefabFactory m_Factory;
};

