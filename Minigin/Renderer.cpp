#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void dae::Renderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

int dae::Renderer::GetOpenGLDriverIndex()
{
	int openglIndex = -1;
	const int driverCount = SDL_GetNumRenderDrivers();

	for (int i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info) && !strcmp(info.name, "opengl"))
			openglIndex = i;
	}
	return openglIndex;
}
void dae::Renderer::Render(float time) const
{
	time;
	bool showDemo = false;
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);
	ImGui::Text("Player 1 controller input (Qbert):");
	ImGui::Text("A: Color changed (25 points)");
	ImGui::Text("X: Remaining disc (50 points)");
	ImGui::Text("Y: Catched Sam or Slick (300 points)");
	ImGui::Text("B: Defeated Coily (500 points)");
	ImGui::Text("RT (or R2): Player died (-1 life)");
	ImGui::Text("");
	ImGui::Text("Player 2 controller input (Coily):");
	ImGui::Text("Dpad down: Color changed (25 points)");
	ImGui::Text("Dpad left: Remaining disc (50 points)");
	ImGui::Text("Dpad up: Catched Sam or Slick (300 points)");
	ImGui::Text("Dpad right: Defeated Qbert (500 points)");
	ImGui::Text("LT (or L2): Player died (-1 life)");
	ImGui::Text("");
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_pRenderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float srcRectX, float srcRectY, float srcRectWidth, float srcRectHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	SDL_Rect src;
	src.x = static_cast<int>(srcRectX);
	src.y = static_cast<int>(srcRectY);
	src.w = static_cast<int>(srcRectWidth);
	src.h = static_cast<int>(srcRectHeight);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float srcRectX, float srcRectY, float srcRectWidth, float srcRectHeight) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_Rect src;
	src.x = static_cast<int>(srcRectX);
	src.y = static_cast<int>(srcRectY);
	src.w = static_cast<int>(srcRectWidth);
	src.h = static_cast<int>(srcRectHeight);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, int x, int y, float scale, SDL_Rect srcRect) const
{
	if (srcRect.w == -1 && srcRect.h == -1)
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &srcRect.w, &srcRect.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = static_cast<int>(srcRect.w * scale);
	dst.h = static_cast<int>(srcRect.h * scale);


	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst);

	
}
