#pragma once
#include <vector>
namespace Horizon
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		void Initialize();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void AddComponent(Component* component);

		template <typename T>
		T* GetComponent() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<Component*> m_pObjectComponents;
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
		return nullptr;
	}
}



