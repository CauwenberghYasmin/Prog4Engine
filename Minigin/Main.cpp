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
#include <imgui.h>
#include <imgui_plot.h>
#include "FpsComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include <filesystem>


namespace fs = std::filesystem;

void CallScene01();
std::vector<float> calculateResultsEx01(int amountSamples)
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

	return (finalResults);
}
static void load()
{
	
	CallScene01();

	//--------------------------------------------------------------------
	//load game stuff



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
	logo->SetPosition(358, 180);
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

	//----------------birds------------------------

	auto cook = std::make_unique<dae::GameObject>();
	auto picture = std::make_unique<dae::RenderComponent>(cook.get(), 563);
	picture->SetTexture("ForwardCook.png");
	picture->SetPosition(300, 300); 
	cook->AddComponent(std::move(picture));

	//auto rotator = std::make_unique<dae::RotatorComponent>(Bird.get(), 523, glm::vec3{ 270, 270, 0}, true, 2.f);
	//Bird->AddComponent(std::move(rotator));
	//-> add move instead

	//so lowkey like "create binding, this thing calls thing function" 


	auto hotdog = std::make_unique<dae::GameObject>();
	auto picture2 = std::make_unique<dae::RenderComponent>(hotdog.get(), 576);
	picture2->SetTexture("ForwardHotDog.png");
	picture2->SetPosition(360, 360); 
	hotdog->AddComponent(std::move(picture2));
																			// give 0, instead of world pos parent!!! -> is local!!
	//auto rotator2 = std::make_unique<dae::RotatorComponent>(Bird2.get(), 513, glm::vec3{ 0, 0, 0 }, false, 4.f);
	//Bird2->AddComponent(std::move(rotator2));
	//same here, add move!

	//Bird2->SetParent(Bird.get(), false);

	scene.Add(std::move(cook));
	scene.Add(std::move(hotdog));
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
