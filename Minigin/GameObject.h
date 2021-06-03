#pragma once
#include <vector>
#include <string>
namespace Horizon
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		GameObject();
		GameObject(const std::string& identifier);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void AddComponent(Component* component);

		template <typename T>
		T* GetComponent() const;
		template <typename T>
		std::vector<T*> GetComponents() const;

		const std::string& GetIdentifier();
		bool Equals(GameObject* pOther) const;

		bool GetIsActive() const;
		void Deactivate();
	private:
		std::vector<Component*> m_pObjectComponents;
		std::string m_Identifier;
		const size_t m_Id;
		static size_t m_LastId;

		bool m_IsActive;
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (Component* pObjectComponent : m_pObjectComponents)
		{
			T* pComponent = dynamic_cast<T*>(pObjectComponent);

			if (pComponent)
				return pComponent;
		}
		Logger::LogWarning("GameObject::GetComponent >> Component could not be found");
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		std::vector<T*> pComponents{};
		for (Component* pObjectComponent : m_pObjectComponents)
		{
			T* pComponent = dynamic_cast<T*>(pObjectComponent);

			if (pComponent)
				pComponents.push_back(pComponent);
		}

		return pComponents;
	}
}



