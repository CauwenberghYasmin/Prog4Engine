
#if _DEBUG
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif

#include <SDL3/SDL_main.h>
#include "Minigin.h"
#include "BurgerTime.h"
#include "Game.h"


//enum Direction { Up, Down, Left, Right };

#include <filesystem>
namespace fs = std::filesystem;


int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	std::unique_ptr<dae::Game> burgerGame = std::make_unique<dae::BurgerTime>();
	dae::Minigin engine(data_location, std::move(burgerGame) ); //put smartpointer here, OWN THE GAME
	engine.Run(); //this empty
    return 0;
}
