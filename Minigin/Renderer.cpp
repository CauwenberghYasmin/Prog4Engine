#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <chrono>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>


void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	m_renderer = SDL_CreateRenderer(window, nullptr);
	if (m_renderer == nullptr)
	{
		std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
#if __EMSCRIPTEN__
	// For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
	// You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
	io.IniFilename = NULL;
#endif

	ImGui_ImplSDL3_InitForSDLRenderer(window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);
}

void dae::Renderer::Render() const
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow(); // For demonstration purposes, do not keep this in your engine

	ImGui::Render();

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy() //doc shows shutdown, but I assume it's this?
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	//if (texture)
	{
		SDL_FRect dst{};
		dst.x = x;
		dst.y = y;
		SDL_GetTextureSize(texture.GetSDLTexture(), &dst.w, &dst.h);
		SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_FRect dst{};
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

//calculations for the graphs
void calculateResultsEx01(int amountSamples)
{
	size_t size = static_cast<size_t>(std::pow(2, 26));
	std::vector<int> numbers(size, 1);

	std::vector<long long> tempResults{};
	std::vector<long long> finalResults{};
	finalResults.resize(11); //have 11 steps

	for (int amount = 0; amount < amountSamples; ++amount)
	{
		tempResults.clear();

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2) {

			auto start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < numbers.size(); i += stepsize)
				numbers[i] *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempResults.push_back(duration);
		}


		for (int time{1} ; time < tempResults.size()-1; ++time)
		{
			finalResults[time-1] += tempResults[time];
		}

	}


	//take average
	for (int time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!
}
void calculateResultsEx02(int amountSamples)
{
	struct transform {
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class gameObject {
	public:
		transform local; //no pointer
		int id;
	};

	size_t size = static_cast<size_t>(std::pow(2, 26));
	std::vector<gameObject> numbers{};
	numbers.resize(size);

	std::vector<long long> tempResults{};
	std::vector<long long> finalResults{};
	finalResults.resize(11); //have 11 steps

	for (int amount = 0; amount < amountSamples; ++amount)
	{
		tempResults.clear();

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2) {

			auto start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < numbers.size(); i += stepsize)
				numbers[i].id *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempResults.push_back(duration);
		}


		for (int time{ 1 }; time < tempResults.size() - 1; ++time)
		{
			finalResults[time - 1] += tempResults[time];
		}

	}


	//take average
	for (int time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!
}
void calculateResultsEx03(int amountSamples)
{
	struct transform {
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class gameObjectAlt {
	public:
		transform* local; //no pointer
		int id;
	};

	size_t size = static_cast<size_t>(std::pow(2, 26));
	std::vector<gameObjectAlt> numbers{};
	numbers.reserve(size);

	std::vector<long long> tempResults{};
	std::vector<long long> finalResults{};
	finalResults.resize(11); //have 11 steps

	for (int amount = 0; amount < amountSamples; ++amount)
	{
		tempResults.clear();

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2) {

			auto start = std::chrono::high_resolution_clock::now();

			for (size_t i = 0; i < numbers.size(); i += stepsize)
				numbers[i].id *= 2;

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			tempResults.push_back(duration);
		}


		for (int time{ 1 }; time < tempResults.size() - 1; ++time)
		{
			finalResults[time - 1] += tempResults[time];
		}

	}


	//take average
	for (int time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!
}