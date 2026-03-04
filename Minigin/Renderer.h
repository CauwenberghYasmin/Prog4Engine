#pragma once
#include <SDL3/SDL.h>
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	

		std::vector<float> calculateResultsEx01(int amountSamples);
		std::vector<float> calculateResultsEx02(int amountSamples);
		std::vector<float> calculateResultsEx03(int amountSamples);
		std::vector<float> results{};
		std::vector<float> results2{};
		std::vector<float> results3{};
		
	public:
		void Init(SDL_Window* window);
		void Render();
		void RenderGraphs();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

