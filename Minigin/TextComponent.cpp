#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "TransformComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"

Horizon::TextComponent::TextComponent(GameObject* parent, const std::string& text, const std::shared_ptr<Font>& font) : Component(parent),
	m_NeedsUpdate{true},
	m_Text{text},
	m_textColor{255,255,255},
	m_pFont{font}
{

}

Horizon::TextComponent::TextComponent(GameObject* parent, const std::string& text, const std::shared_ptr<Font>& font, const Color& textColor) : Component(parent),
	m_NeedsUpdate{true},
	m_Text{ text },
	m_textColor{ textColor.r,textColor.g,textColor.b },
	m_pFont{ font }
{

}

void Horizon::TextComponent::Initialize()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
}

void Horizon::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { m_textColor.r,m_textColor.g,m_textColor.b }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void Horizon::TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		if (m_pTransformComponent)
		{
			const auto pos = m_pTransformComponent->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
		else
			Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0);
	}
}

void Horizon::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

const std::string& Horizon::TextComponent::GetText() const
{
	return m_Text;
}