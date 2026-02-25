#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
  

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
#include "FpsComponent.h"
#include "RenderComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

void CallScene01();

static void load()
{
	
	CallScene01();

	//--------------------------------------------------------------------
	//load game stuff


	//get raw pointer out of smart by using.get()




}

void CallScene01()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();


	auto scene01 = std::make_unique<dae::GameObject>();

	auto background = std::make_unique<dae::RenderComponent>(scene01.get(), 33);
	background->SetTexture("background.png");
	
	scene01->AddComponent(std::move(background));
	scene.Add(std::move(scene01));


	auto scene02 = std::make_unique<dae::GameObject>();
	auto logo = std::make_unique<dae::RenderComponent>(scene02.get(), 23);
	logo->SetTexture("logo.png");
	logo->SetPosition(358, 180); //counts as transform component?
	scene02->AddComponent(std::move(logo));
	scene.Add(std::move(scene02));

	//title assignment
	auto textObject = std::make_unique<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textTitleComponent = std::make_unique<dae::TextComponent>(textObject.get(), "Programming 4 Assignment", font, 1); //don't need this component ref anymore, so no need to safe the id
	textTitleComponent->SetColor({ 255, 255, 0, 255 });
	textTitleComponent->SetPosition(292, 20);
	textObject->AddComponent(std::move(textTitleComponent));

	auto textRenderer = std::make_unique<dae::RenderComponent>(textObject.get(), 13);
	textObject->AddComponent(std::move(textRenderer));	//everything that wants to get rendered (like text) needs a render component!

	scene.Add(std::move(textObject));

	//add fps component -> has on it's own: 
	auto fpsObject = std::make_unique<dae::GameObject>();

	auto fpsComp = std::make_unique<dae::FPSComponent>(fpsObject.get(), 14);
	auto textComp = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS: 0", font, 2);
	auto textRenderer2 = std::make_unique<dae::RenderComponent>(fpsObject.get(), 83);

	fpsObject->AddComponent(std::move(textRenderer2));
	fpsObject->AddComponent(std::move(textComp));
	fpsObject->AddComponent(std::move(fpsComp));


	scene.Add(std::move(fpsObject));
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
