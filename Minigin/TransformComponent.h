#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* parent, int x, int y, int z);
		const IPoint3& GetPosition() const;
		void SetPosition(int x, int y, int z);
		void Move(int x, int y, int z);
	private:
		IPoint3 m_Position;
	};
}