#include "MiniginPCH.h"
#include "PrefabFactory.h"

using namespace dae;

Prefab* PrefabFactory::GetPrefab(const rapidjson::Value& jsonValue)
{
	const std::string className = jsonValue["class"].GetString();
	const std::string key = "class " + className;
	
	const auto it = m_Generators.find(key);

	if (it == m_Generators.end())
	{
		Logger::LogWarning("PrefabFactory::GetPrefab: class is not part of generators, returning nullptr");
		return nullptr;
	}

	return it->second(jsonValue);
}
