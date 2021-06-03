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

		GameObject* GetParent() const;
		const std::string& GetIdentifier();

		Component(GameObject* parent);
		Component(GameObject* parent, const std::string& identifier);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		bool Equals(Component* pOther) const;
	protected:
		GameObject* m_pGameObject = nullptr;
		std::string m_Identifier;
		const size_t m_Id;
		static size_t m_LastId;
	};
}
