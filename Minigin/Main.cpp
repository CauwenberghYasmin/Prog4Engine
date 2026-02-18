#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
  
#include <vld.h>

#if _DEBUG
	#if __has_include(<vld.h>)
	#include <vld.h>
	#endif
#endif


#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	//adding texture component
	auto scene01 = std::make_unique<dae::GameObject>();
	scene01->SetTexture("background.png");
	scene.Add(std::move(scene01));

	//adding 2nd texture component
	scene01 = std::make_unique<dae::GameObject>();
	scene01->SetTexture("logo.png");
	scene01->SetPosition(358, 180); //counts as transform component?
	scene.Add(std::move(scene01));

	//adding text component
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textTitle = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	textTitle->SetColor({ 255, 255, 0, 255 });
	textTitle->SetPosition(292, 20);
	//scene.Add(textTitle); 


	//add fps component -> has on it's own: 
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
