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
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "RotatorComponent.h"
#include <filesystem>
#include "InputManager.h"
#include "InputOptions.h"
#include "Command.h"
#include "KeyboardInput.h"
#include "Xinput.h"
#include <string>
#include "ObserverManager.h"
#include "Observer.h"

enum Direction { Up, Down, Left, Right };

namespace fs = std::filesystem;

namespace dae {

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
	//load game stuff for testing
	//-> make seperate engine eventually!!!!



}



void CallScene01()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& inputManager = dae::InputManager::GetInstance();
	auto& ObserverManager = dae::ObserverManager::GetInstance();


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

	//----controls------
	auto ControlsTextObject = std::make_unique<dae::GameObject>();

	auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
	auto textControllerComponent = std::make_unique<dae::TextComponent>(ControlsTextObject.get(), "Use D-Pad to move HotDogMan, X to inflict damage, and A to pick up pellets.", textFont, 1); //don't need this component ref anymore, so no need to safe the id
	textControllerComponent->SetColor({ 255, 255, 255, 255 });
	textControllerComponent->SetPosition(10, 100);
	ControlsTextObject->AddComponent(std::move(textControllerComponent));

	auto textControllerRenderer = std::make_unique<dae::RenderComponent>(ControlsTextObject.get(), 17);
	ControlsTextObject->AddComponent(std::move(textControllerRenderer));	//everything that wants to get rendered (like text) needs a render component!
	scene.Add(std::move(ControlsTextObject));
	//-------------
	auto ControlsTextObject2 = std::make_unique<dae::GameObject>();

	auto textControllerComponent2 = std::make_unique<dae::TextComponent>(ControlsTextObject2.get(), "Use WASD to move Chef, Z to inflict damage, and X to pick up pellets. ", textFont, 1);
	textControllerComponent2->SetColor({ 255, 255, 255, 255 });
	textControllerComponent2->SetPosition(10, 130);
	ControlsTextObject2->AddComponent(std::move(textControllerComponent2));

	auto textControllerRenderer2 = std::make_unique<dae::RenderComponent>(ControlsTextObject2.get(), 17);
	ControlsTextObject2->AddComponent(std::move(textControllerRenderer2));
	scene.Add(std::move(ControlsTextObject2));

	//-----end controlls-----

	//add fps component -> has on it's own: 
	auto fpsObject = std::make_unique<dae::GameObject>();

	auto fpsComp = std::make_unique<dae::FPSComponent>(fpsObject.get(), 14);
	auto textComp = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS: 0", font, 2);
	auto textRenderer2 = std::make_unique<dae::RenderComponent>(fpsObject.get(), 83);

	fpsObject->AddComponent(std::move(textRenderer2));
	fpsObject->AddComponent(std::move(textComp));
	fpsObject->AddComponent(std::move(fpsComp));
	scene.Add(std::move(fpsObject));

	//----------------Players------------------------

	auto cook = std::make_unique<dae::GameObject>();
	auto picture = std::make_unique<dae::RenderComponent>(cook.get(), 563);
	picture->SetTexture("ForwardCook.png");
	picture->SetPosition(300, 300); 
	cook->AddComponent(std::move(picture));

	//adding health component
	auto HealthComponent = std::make_unique<dae::HealthComponent>(cook.get(), 37802, 3);
//	int startHealthCook{ HealthComponent->GetCurrentHealth() };
	cook->AddComponent(std::move(HealthComponent));

	auto ScoreComponent = std::make_unique<dae::ScoreComponent>(cook.get(), 372102);
//	int startScoreCook{ ScoreComponent->GetCurrentScore() };
	cook->AddComponent(std::move(ScoreComponent));

	//auto textHealth = std::make_unique<dae::TextComponent>(cook.get(), std::to_string(startHealthCook), textFont, 1);
	//textHealth->SetColor({ 255, 255, 255, 255 });
	//textHealth->SetPosition(10, 330);
	//cook->AddComponent(std::move(textHealth)); //add renderer!
		

	float cookSpeed{ 9600.f };
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Up, cookSpeed))
		,SDL_SCANCODE_W, InputState::Pressed);
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Down, cookSpeed)),
		SDL_SCANCODE_S, InputState::Pressed);
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Left, cookSpeed)),
		SDL_SCANCODE_A, InputState::Pressed);
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Right, cookSpeed)),
		SDL_SCANCODE_D, InputState::Pressed);

	//added binding, but still need to add component + set starting health 
	const int amountLivesTaken{ -1 };
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::HealthCommand>(cook.get(), amountLivesTaken)),
		SDL_SCANCODE_Z, InputState::Pressed);
	const int amountScoreAdded {150};
	inputManager.GetKeyboardInput()->AddBinding(
		(std::make_unique<dae::HealthCommand>(cook.get(), amountScoreAdded)),
		SDL_SCANCODE_X, InputState::Pressed);

	GameEvent* event{ new GameEvent};
	ObserverManager.AddObserver(cook.get(), event);

	//----------------------hotdog man---------------------------------------
	auto hotdog = std::make_unique<dae::GameObject>();
	auto picture2 = std::make_unique<dae::RenderComponent>(hotdog.get(), 576);
	picture2->SetTexture("ForwardHotDog.png");
	picture2->SetPosition(360, 360); 
	hotdog->AddComponent(std::move(picture2));

	//adding health component
	auto HealthComponent2 = std::make_unique<dae::HealthComponent>(hotdog.get(), 4135, 3);
	int startHealtDog{ HealthComponent2->GetCurrentHealth() };
	hotdog->AddComponent(std::move(HealthComponent2));

	auto ScoreComponent2 = std::make_unique<dae::ScoreComponent>(hotdog.get(), 12589);
	int startScoreDog{ ScoreComponent2->GetCurrentScore() };
	hotdog->AddComponent(std::move(ScoreComponent2));

	float HotdogSpeed{ 15600.f };
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Up, HotdogSpeed)),
		XINPUT_GAMEPAD_DPAD_UP, InputState::Pressed);
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Down, HotdogSpeed)),
		XINPUT_GAMEPAD_DPAD_DOWN, InputState::Pressed);
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Left, HotdogSpeed)),
		XINPUT_GAMEPAD_DPAD_LEFT, InputState::Pressed);
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Right, HotdogSpeed)),
		XINPUT_GAMEPAD_DPAD_RIGHT, InputState::Pressed);

	const int amountLivesTaken2{ -1 };
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::HealthCommand>(hotdog.get(), amountLivesTaken2)),
		XINPUT_GAMEPAD_X, InputState::Pressed);
	const int amountScoreAdded2{ 150 };
	inputManager.GetControllerInput(0)->AddBinding(
		(std::make_unique<dae::HealthCommand>(hotdog.get(), amountScoreAdded2)),
		XINPUT_GAMEPAD_A, InputState::Pressed);
	


	
	//--------------health output 01--------------------------
	auto HealthOutput1 = std::make_unique<dae::GameObject>();

	auto textHealth = std::make_unique<dae::TextComponent>(HealthOutput1.get(), std::string("Amount Lives: 3"), textFont, 1); //don't need this component ref anymore, so no need to safe the id
	textHealth->SetColor({ 255, 255, 255, 255 });
	textHealth->SetPosition(20, 300);
	HealthOutput1->AddComponent(std::move(textHealth));

	auto HealthOutput1Renderer = std::make_unique<dae::RenderComponent>(HealthOutput1.get(), 17);
	HealthOutput1->AddComponent(std::move(HealthOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!
	scene.Add(std::move(HealthOutput1));
	

	//--------------Score output 01--------------------------
	auto scoreOutput1 = std::make_unique<dae::GameObject>();

	auto textscore = std::make_unique<dae::TextComponent>(scoreOutput1.get(), std::string("Amount score: 0"), textFont, 1); //don't need this component ref anymore, so no need to safe the id
	textscore->SetColor({ 255, 255, 255, 255 });
	textscore->SetPosition(20, 330);
	scoreOutput1->AddComponent(std::move(textscore));

	auto scoreOutput1Renderer = std::make_unique<dae::RenderComponent>(scoreOutput1.get(), 17);
	scoreOutput1->AddComponent(std::move(scoreOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!
	scene.Add(std::move(scoreOutput1));

	//--------------health output 02--------------------------
	auto HealthOutput2 = std::make_unique<dae::GameObject>();

	auto textHealth2 = std::make_unique<dae::TextComponent>(HealthOutput2.get(), std::string("Amount Lives: " + std::to_string(startHealtDog)), textFont, 1); //don't need this component ref anymore, so no need to safe the id
	textHealth2->SetColor({ 255, 255, 255, 255 });
	textHealth2->SetPosition(20, 380);
	HealthOutput2->AddComponent(std::move(textHealth2));

	auto HealthOutput1Renderer2 = std::make_unique<dae::RenderComponent>(HealthOutput2.get(), 17);
	HealthOutput2->AddComponent(std::move(HealthOutput1Renderer2));	//everything that wants to get rendered (like text) needs a render component!
	scene.Add(std::move(HealthOutput2));

	//--------------Score output 02--------------------------
	auto scoreOutput2 = std::make_unique<dae::GameObject>();

	auto textscore2 = std::make_unique<dae::TextComponent>(scoreOutput2.get(), std::string("Amount score: " + std::to_string(startScoreDog)), textFont, 1); //don't need this component ref anymore, so no need to safe the id
	textscore2->SetColor({ 255, 255, 255, 255 });
	textscore2->SetPosition(20, 410);
	scoreOutput2->AddComponent(std::move(textscore2));

	auto scoreOutput1Renderer2 = std::make_unique<dae::RenderComponent>(scoreOutput2.get(), 17);
	scoreOutput2->AddComponent(std::move(scoreOutput1Renderer2));	//everything that wants to get rendered (like text) needs a render component!
	scene.Add(std::move(scoreOutput2));

	scene.Add(std::move(cook));
	scene.Add(std::move(hotdog));
}
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
	engine.Run(dae::load);
    return 0;
}
