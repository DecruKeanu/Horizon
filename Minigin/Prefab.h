#pragma once
namespace Horizon
{
	class GameObject;

	class Prefab
	{
	public:
		virtual ~Prefab() = default;
		GameObject* GetGameObject() const;
	protected:
		void SetGameObject(GameObject* pGameObject);
	private:
		GameObject* m_pGameObject = nullptr;
	};
}
