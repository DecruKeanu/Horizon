#pragma once
#include <functional>
#include <unordered_map>
#include <memory>
#include "Prefab.h"
#include "rapidjson.h"
#include "document.h"

//Credit to Elise Briers
namespace Horizon
{
	class PrefabFactory final
	{
		using generator = std::function<Prefab*(const rapidjson::Value&)>;
		using generatorMap = std::unordered_map<std::string, generator>;

	public:
		PrefabFactory() = default;

		template <typename T>
		void RegisterPrefab();
		Prefab* GetPrefab(const rapidjson::Value& jsonValue);
	private:
		template <typename T>
		static Prefab* DefaultAllocator(const rapidjson::Value& jsonObject);
		generatorMap m_Generators;
	};

	template<typename T>
	inline void PrefabFactory::RegisterPrefab()
	{
		const std::string className = typeid(T).name();
		m_Generators[className] = DefaultAllocator<T>;
	}

	template<typename T>
	inline Prefab* PrefabFactory::DefaultAllocator(const rapidjson::Value& jsonObject)
	{
		return new T(jsonObject);
	}
}

