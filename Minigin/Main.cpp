#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
  
#include <vld.h>

//#if _DEBUG
//	#if __has_include(<vld.h>)
//	#include <vld.h>
//	#endif
//#endif

#ifdef USE_VLD
#include <vld.h>
#endif


#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "FpsComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	
	auto scene01 = std::make_unique<dae::GameObject>();
	scene01->SetTexture("background.png");
	//-> say add instead(fill parameters in with constructor)
	scene.Add(std::move(scene01));
	
	scene01 = std::make_unique<dae::GameObject>();
	scene01->SetTexture("logo.png");
	scene01->SetPosition(358, 180); //counts as transform component?
	scene.Add(std::move(scene01));

	//title assignment
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textTitleComponent = std::make_unique<dae::TextObject>("Programming 4 Assignment", font, 1.f); //don't need this component ref anymore, so no need to safe the id
	textTitleComponent->SetColor({ 255, 255, 0, 255 });
	textTitleComponent->SetPosition(292, 20);
	
	auto textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent(std::move(textTitleComponent));
	scene.Add(std::move (textObject));

	//add fps component -> has on it's own: 
	auto textComp = std::make_unique<dae::TextObject>("FPS: 0", font, 2.f);
	auto textPtr = textComp.get(); // Get the raw pointer to give to the FPS component
	
	auto fpsObject = std::make_unique<dae::GameObject>();
	fpsObject->AddComponent(std::move(textComp));

	auto fpsComp = std::make_unique<dae::FPSComponent>(textPtr, 3.f);
	fpsObject->AddComponent(std::move(fpsComp));

	scene.Add(std::move(fpsObject));

	//--------------------------------------------------------------------
	//load game stuff

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
