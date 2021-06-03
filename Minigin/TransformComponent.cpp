#include "MiniginPCH.h"
#include "TransformComponent.h"

Horizon::TransformComponent::TransformComponent(GameObject* parent, int x, int y) : Component(parent),
m_Position{ x,y}
{

}

const Horizon::IPoint2& Horizon::TransformComponent::GetPosition() const
{
	return m_Position;
}

void Horizon::TransformComponent::SetPosition(int x, int y)
{
	m_Position = { x,y};
}

void Horizon::TransformComponent::SetPosition(const IPoint2& pos)
{
	m_Position = pos;
}

void Horizon::TransformComponent::Move(int x, int y)
{
	SetPosition(m_Position.x + x, m_Position.y + y);
}
