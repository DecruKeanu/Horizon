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

	protected:
		virtual void Initialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		void Add(GameObject* object);

	private: 
		std::string m_Name;
		std::vector<GameObject*> m_pObjects{};

		bool m_IsInitialized;
		static unsigned int m_IdCounter; 
	};

}
