#pragma once
#include <string>
namespace Horizon
{
	class GameObject;

	class Prefab
	{
	public:
		virtual ~Prefab() = default;
		GameObject* GetGameObject() const;
		const std::string& GetPrefabName() { return m_PrefabName; };
	protected:
		void SetGameObject(GameObject* pGameObject);
		void SetPrefabName(const std::string& prefabName) { m_PrefabName = prefabName; };
	private:
		GameObject* m_pGameObject = nullptr;
		std::string m_PrefabName;
	};
}
