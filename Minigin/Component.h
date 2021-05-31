#pragma once
#include "GameObject.h"

namespace Horizon
{
	class Component
	{
	public:
		virtual void Initialize() {};
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		Component(GameObject* parent);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		GameObject* m_pGameObject = nullptr;
	};
}
