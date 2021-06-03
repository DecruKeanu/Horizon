#pragma once
#include "Component.h"

namespace Horizon
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* parent, int x, int y);
		const IPoint2& GetPosition() const;
		void SetPosition(int x, int y);
		void SetPosition(const IPoint2& pos);
		void Move(int x, int y);
	private:
		IPoint2 m_Position;
	};
}