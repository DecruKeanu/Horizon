#include "MiniginPCH.h"
#include "TransformComponent.h"

Horizon::TransformComponent::TransformComponent(GameObject* parent, int x, int y, int z) : Component(parent),
m_Position{ x,y,z }
{
}

const Horizon::IPoint3& Horizon::TransformComponent::GetPosition() const
{
	return m_Position;
}

void Horizon::TransformComponent::SetPosition(int x, int y, int z)
{
	m_Position = { x,y,z };
}

void Horizon::TransformComponent::Move(int x, int y, int z)
{
	const IPoint3 pos = GetPosition();

	SetPosition(pos.x + x, pos.y + y, pos.z + z);
}
