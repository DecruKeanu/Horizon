#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

void Horizon::Renderer::Init(SDL_Window* window)
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

int Horizon::Renderer::GetOpenGLDriverIndex()
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
void Horizon::Renderer::Render(float time) const
{
	time;
	bool showDemo = false;
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	if (showDemo)
	{
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
	}

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(m_pRenderer);
}

void Horizon::Renderer::Destroy()
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

void Horizon::Renderer::RenderTexture(const Texture2D& texture, const int x, const int y) const
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Horizon::Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, const int width, const int height) const
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Horizon::Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, const float scale, SDL_Rect srcRect) const
{
	if (srcRect.w == -1 && srcRect.h == -1)
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &srcRect.w, &srcRect.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = int(srcRect.w * scale);
	dst.h = int(srcRect.h * scale);


	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst);


}
