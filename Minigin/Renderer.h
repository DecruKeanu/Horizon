#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Horizon
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render(float time) const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const int x, const int y) const;
		void RenderTexture(const Texture2D& texture, const int x, const int y, const int width, const int height) const;

		void RenderTexture(const Texture2D& texture, const int x, const int y, const float scale, SDL_Rect srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

		void DrawSDLRect(const SDL_Color& color, const SDL_Rect* rect);
	private:
		int GetOpenGLDriverIndex();
		SDL_Renderer* m_pRenderer = nullptr;
		SDL_Window* m_pWindow = nullptr;
	};
}

