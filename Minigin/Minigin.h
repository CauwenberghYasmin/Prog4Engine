#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <chrono>
#include "Game.h"
#include "BurgerTime.h"

namespace dae
{
	class Minigin final
	{
		bool m_quit{};
	public:
		explicit Minigin(const std::filesystem::path& dataPath, std::unique_ptr<Game> currentGame);
		~Minigin();
		void Run();
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> last_time{}; //= std::chrono::high_resolution_clock::now();
		std::unique_ptr<Game> m_CurrentGame;
	
	};
}