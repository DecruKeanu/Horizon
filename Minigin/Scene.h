#pragma once
#include "SceneManager.h"

namespace Horizon
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void RootInitialize();
		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

		GameObject* GetGameObject(const std::string& identifier);
		std::vector<GameObject*> GetGameObjects(const std::string& identifier);

		void Add(GameObject* object);
		void Remove(GameObject* pObject);

	protected:
		virtual void Initialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};



	private: 
		std::string m_Name;
		std::vector<GameObject*> m_pObjects{};

		bool m_IsInitialized;
		static unsigned int m_IdCounter; 
	};

}
