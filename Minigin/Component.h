#pragma once
#include "GameObject.h"

namespace Horizon
{
	class Component
	{
	public:
		Component(GameObject* parent);
		Component(GameObject* parent, const std::string& identifier);
		virtual ~Component() = default;
		Component(const Component & other) = delete;
		Component(Component && other) = delete;
		Component& operator=(const Component & other) = delete;
		Component& operator=(Component && other) = delete;

		virtual void Initialize() {};
		virtual void PostInitialize() {};
		virtual void FixedUpdate() {};
		virtual void PersistentUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		virtual void Reset() {};

		GameObject* GetParent() const;
		const std::string& GetIdentifier() const;

		bool Equals(Component* pOther) const;
	protected:
		GameObject* m_pGameObject = nullptr;
		std::string m_Identifier;
		const size_t m_Id;
		static size_t m_LastId;
	};
}
