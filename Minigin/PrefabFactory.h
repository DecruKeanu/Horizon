#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include "GameObject.h"
#include "rapidjson.h"
#include "document.h"

//Credit to Elise Briers for helping me template the PrefabFactory

namespace Horizon
{
	class PrefabFactory final
	{
		using generator = std::function<GameObject*(const rapidjson::Value&)>;
		using generatorMap = std::unordered_map<std::string, generator>;

	public:
		PrefabFactory() = default;

		template <typename T>
		void RegisterPrefab();
		GameObject* GetPrefab(const rapidjson::Value& jsonValue) const;
	private:
		template <typename T>
		static GameObject* DefaultAllocator(const rapidjson::Value& jsonObject);
		generatorMap m_Generators;
	};

	template<typename T>
	inline void PrefabFactory::RegisterPrefab()
	{
		const std::string className = typeid(T).name();
		m_Generators[className] = DefaultAllocator<T>;
	}

	template<typename T>
	inline GameObject* PrefabFactory::DefaultAllocator(const rapidjson::Value& jsonObject)
	{
		T object = T(jsonObject);
		return object.GetGameObject();
	}
}

