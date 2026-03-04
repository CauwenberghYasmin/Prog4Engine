#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <imgui_plot.h>
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

void dae::Renderer::Render()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(); // For demonstration purposes, do not keep this in your engine
	RenderGraphs();
	ImGui::Render();

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);

	
	

}

void dae::Renderer::RenderGraphs()
{
	constexpr float xValues[]{1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 512.f, 1024.f};
	static bool showPlot = false;
	static bool showPlot2 = false;
	static bool showPlot3 = false;
	static int samples = 10;
	static int samples2 = 10;
	

	ImGui::Begin("Ex01");
	ImGui::SetNextWindowSize(ImVec2(300, 300));
	ImGui::InputInt("Amount samples", &samples, 1);

	if (ImGui::Button("trash the cach"))
	{
		results = calculateResultsEx01(samples);
		showPlot = true;
	}
	if (showPlot && !results.empty())
	{
		ImGui::PlotConfig conf{};
		conf.values.xs = xValues;
		conf.values.ys = results.data();
		conf.values.count = static_cast<int>(results.size());
		conf.values.color = 0xFF'00'7F'FF;
		conf.scale.min = 0;
		conf.scale.max = *std::max_element(results.begin(), results.end());
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.0f, y=%.5f";
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.frame_size = ImVec2{ 200, 100 };
		conf.line_thickness = 2.f;
		ImGui::Plot("results", conf);
	}
	ImGui::End();

	ImGui::Begin("Ex02 and 03");
	ImGui::SetNextWindowSize(ImVec2(300, 800)); 
	ImGui::SetWindowPos(ImVec2(500, 50));
	ImGui::InputInt("Amount samples", &samples2, 1);

	// --- GRAPH 1: gameObject3D ---
	if (ImGui::Button("trash the cach with gameObject3D"))
	{
		results2 = calculateResultsEx02(samples2);
		showPlot2 = true;
	}
	if (showPlot2 && !results2.empty())
	{
		ImGui::PlotConfig conf2{};
		conf2.values.xs = xValues;
		conf2.values.ys = results2.data();
		conf2.values.count = static_cast<int>(results2.size());
		conf2.values.color = 0xFF'00'7F'FF;
		conf2.scale.min = 0;
		conf2.scale.max = *std::max_element(results2.begin(), results2.end());
		conf2.tooltip.show = true;
		conf2.tooltip.format = "x=%.0f, y=%.5f";
		conf2.grid_x.show = true;
		conf2.grid_y.show = true;
		conf2.frame_size = ImVec2{ 200, 100 };
		conf2.line_thickness = 2.f;
		ImGui::Plot("Ex02", conf2);
	}
	if (ImGui::Button("trash the cach with gameObject3DAlt"))
	{
		results3 = calculateResultsEx03(samples2);
		showPlot3 = true;
	}
	if (showPlot3 && !results3.empty())
	{
		ImGui::PlotConfig conf3{};
		conf3.values.xs = xValues;
		conf3.values.ys = results3.data();
		conf3.values.count = static_cast<int>(results3.size());
		conf3.values.color = 0xFF'FF'7F'00;
		conf3.scale.min = 0;
		conf3.scale.max = *std::max_element(results3.begin(), results3.end());
		conf3.tooltip.show = true;
		conf3.tooltip.format = "x=%.0f, y=%.5f";
		conf3.grid_x.show = true;
		conf3.grid_y.show = true;
		conf3.frame_size = ImVec2{ 200, 100 };
		conf3.line_thickness = 2.f;
		ImGui::Plot("Ex03", conf3);
	}
	if (showPlot2 && showPlot3 && !results2.empty() && !results3.empty())
	{
		ImGui::Text("Combined Results");
		const float* y_data[] = { results2.data(), results3.data() };
		ImU32 colors[2] = { 0xFF'00'7F'FF, 0xFF'FF'7F'00 }; 
		float max2 = *std::max_element(results2.begin(), results2.end());
		float max3 = *std::max_element(results3.begin(), results3.end());

		ImGui::PlotConfig conf_merged{};
		conf_merged.values.xs = xValues;
		conf_merged.values.ys_list = y_data;
		conf_merged.values.ys_count = 2;
		conf_merged.values.colors = colors;

		conf_merged.values.count = static_cast<int>(results2.size()); //both same size
		conf_merged.scale.min = 0;
		conf_merged.scale.max = std::max(max2, max3); // Use the highest value of both
		conf_merged.tooltip.show = true;
		conf_merged.tooltip.format = "x=%.0f, y=%.5f";
		conf_merged.grid_x.show = true;
		conf_merged.grid_y.show = true;
		conf_merged.frame_size = ImVec2{ 200, 100 };
		conf_merged.line_thickness = 2.f;

		ImGui::Plot("Merged", conf_merged); 
	}

	ImGui::End();
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
std::vector<float> dae::Renderer::calculateResultsEx01(int amountSamples)
{
	size_t size = static_cast<size_t>(std::pow(2, 26));
	std::vector<int> numbers(size, 1);

	std::vector<long long> tempResults{};
	std::vector<float> finalResults{};
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


		for (size_t time{1} ; time < tempResults.size()-1; ++time)
		{
			finalResults[time-1] += static_cast<float>(tempResults[time]);
		}

	}


	//take average
	for (size_t time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!

	return (finalResults);
}
std::vector<float> dae::Renderer::calculateResultsEx02(int amountSamples)
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
		transform local{}; //no pointer
		int id{};
	};

	size_t size = static_cast<size_t>(std::pow(2, 26));
	std::vector<gameObject> numbers{};
	numbers.resize(size);

	std::vector<long long> tempResults{};
	std::vector<float> finalResults{};
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


		for (size_t time{ 1 }; time < tempResults.size() - 1; ++time)
		{
			finalResults[time - 1] += static_cast<float>(tempResults[time]);
		}

	}


	//take average
	for (size_t time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!

	return finalResults;
}
std::vector<float> dae::Renderer::calculateResultsEx03(int amountSamples)
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
	numbers.resize(size);

	std::vector<long long> tempResults{};
	std::vector<float> finalResults{};
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


		for (size_t time{ 1 }; time < tempResults.size() - 1; ++time)
		{
			finalResults[time - 1] += static_cast<float>(tempResults[time]);
		}

	}


	//take average
	for (size_t time{ 0 }; time < finalResults.size(); ++time)
	{
		finalResults[time] /= amountSamples;
	} //don't forget to take out first and last later!

	return finalResults;
}