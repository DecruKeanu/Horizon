#pragma once

namespace dae
{
	class Texture2D;
	class ObjectComponent;

	class GameObject final
	{
	public:
		void BeginPlay();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void AddComponent(ObjectComponent* component);

		template <typename T>
		T* GetComponent() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<ObjectComponent*> m_pObjectComponents;
	};

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (ObjectComponent* pObjectComponent : m_pObjectComponents)
		{
			T* pComponent = dynamic_cast<T*>(pObjectComponent);

			if (pComponent)
				return pComponent;
		}
		return nullptr;
	}
}



