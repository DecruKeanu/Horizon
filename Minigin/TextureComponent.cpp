#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

Horizon::TextureComponent::TextureComponent(GameObject* parent,const std::string textureFile) : Component(parent),
	m_SrcRect{0,0,-1,-1},
	m_Scale{1.f}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(textureFile);
}

void Horizon::TextureComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
}

void Horizon::TextureComponent::Render() const
{
	if (m_pTransformComponent)
	{
		const auto& pos = m_pTransformComponent->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, int(pos.x),int(pos.y),m_Scale, m_SrcRect);
	}
	else
		Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0, m_Scale, m_SrcRect);
}

void Horizon::TextureComponent::SetSrcRect(int x, int y, int width, int height)
{
	m_SrcRect = { x,y,width,height };
}

void Horizon::TextureComponent::SetScale(float scale)
{
	m_Scale = scale;
}
