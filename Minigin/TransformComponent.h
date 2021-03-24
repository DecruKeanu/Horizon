#pragma once
//#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
//#pragma warning(pop)
#include "ObjectComponent.h"

namespace dae
{
	class GameObject;

	class TransformComponent final : public ObjectComponent
	{
	public:
		TransformComponent(GameObject* parent, float x, float y, float z);
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}