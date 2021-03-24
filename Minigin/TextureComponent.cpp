#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(GameObject* parent,const std::string textureFile) : dae::ObjectComponent(parent)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureFile);
}

void dae::TextureComponent::BeginPlay()
{
	m_pTransformComponent = m_pGameObject->GetComponent<dae::TransformComponent>();
}

void dae::TextureComponent::Render() const
{
	if (m_pTransformComponent)
	{
		const auto& pos = m_pTransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0);
}