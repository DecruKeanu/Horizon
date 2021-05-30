#pragma once
namespace dae
{
	class GameObject;

	class Prefab
	{
	public:
		virtual ~Prefab() = default;
		dae::GameObject* GetGameObject() const;
	protected:
		void SetGameObject(dae::GameObject* pGameObject);
	private:
		dae::GameObject* m_pGameObject = nullptr;
	};
}
