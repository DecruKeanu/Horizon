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
