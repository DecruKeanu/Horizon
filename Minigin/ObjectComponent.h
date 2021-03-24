#pragma once
#include "GameObject.h"

namespace dae
{
	class ObjectComponent
	{
	public:
		virtual void BeginPlay() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		ObjectComponent(GameObject* parent);
		virtual ~ObjectComponent() = default;
		ObjectComponent(const ObjectComponent& other) = delete;
		ObjectComponent(ObjectComponent&& other) = delete;
		ObjectComponent& operator=(const ObjectComponent& other) = delete;
		ObjectComponent& operator=(ObjectComponent&& other) = delete;

	protected:
		GameObject* m_pGameObject = nullptr;
	};
}
