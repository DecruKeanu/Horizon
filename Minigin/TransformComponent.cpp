#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* parent, int x, int y, int z) : Component(parent),
m_Position{ x,y,z }
{
}

const IPoint3& dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetPosition(int x, int y, int z)
{
	m_Position = { x,y,z };
}

void dae::TransformComponent::Move(int x, int y, int z)
{
	const IPoint3 pos = GetPosition();

	SetPosition(pos.x + x, pos.y + y, pos.z + z);
}
