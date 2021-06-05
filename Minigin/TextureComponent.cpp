#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

Horizon::TextureComponent::TextureComponent(GameObject* parent, const std::string textureFile) : Component(parent),
m_SrcRect{ 0,0,-1,-1 },
m_Scale{ 1.f },
m_TextureOffset{}
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
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_TextureOffset.x, pos.y + m_TextureOffset.y, m_Scale, m_SrcRect);
		return;
	}
	Logger::LogWarning("TextureComponent::Render >> GameObject does not have transformComponent, renderPos = (0,0)");
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

void Horizon::TextureComponent::SetTextureOffset(const IPoint2& offset)
{
	m_TextureOffset = offset;
}
