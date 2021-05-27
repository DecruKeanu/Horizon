#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* parent, float x, float y, float z) : Component(parent),
	m_Position{ x,y,z }
{

}

const glm::vec3& dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3{ x,y,z };
}