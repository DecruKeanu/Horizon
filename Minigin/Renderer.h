#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
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

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		void RenderTexture(const Texture2D& texture, float x, float y, float srcRectX, float srcRectY, float srcRectWidth, float srcRectHeight) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float srcRectX, float srcRectY, float srcRectWidth, float srcRectHeight) const;

		void RenderTexture(const Texture2D& texture, int x, int y, float scale, SDL_Rect srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
	private:
		int GetOpenGLDriverIndex();
		SDL_Renderer* m_pRenderer = nullptr;
		SDL_Window* m_pWindow = nullptr;
	};
}

