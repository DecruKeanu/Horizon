#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(GameObject* parent,const std::string textureFile) : dae::Component(parent),
	m_SrcRect{0,0,-1,-1},
	m_Scale{1.f}
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(textureFile);
}

void dae::TextureComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<dae::TransformComponent>();
}

void dae::TextureComponent::Render() const
{
	if (m_pTransformComponent)
	{
		const auto& pos = m_pTransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, int(pos.x),int(pos.y),m_Scale, m_SrcRect);
	}
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0, m_Scale, m_SrcRect);
}

void dae::TextureComponent::SetSrcRect(int x, int y, int width, int height)
{
	m_SrcRect = { x,y,width,height };
}

void dae::TextureComponent::SetScale(float scale)
{
	m_Scale = scale;
}
