#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Horizon::Font::GetFont() const {
	return m_pFont;
}

Horizon::Font::Font(const std::string& fullPath, unsigned int size) : m_pFont(nullptr), m_Size(size)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Horizon::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}
