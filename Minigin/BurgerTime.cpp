#include "BurgerTime.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
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
#include <string>
#include "ObserverManager.h"
#include "Observer.h"

enum Direction { Up, Down, Left, Right };

namespace fs = std::filesystem;
namespace dae {


	BurgerTime::BurgerTime() :
		Game()
	{
	}

	BurgerTime::~BurgerTime() = default;

	
	void BurgerTime::Initialize()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene();
		auto& inputManager = dae::InputManager::GetInstance();
		//auto& ObserverManager = dae::ObserverManager::GetInstance();


		auto scene01 = std::make_unique<dae::GameObject>();

		auto background = std::make_unique<dae::RenderComponent>(scene01.get());
		background->SetTexture("background.png");

		scene01->AddComponent(std::move(background));
		scene.Add(std::move(scene01));


		auto scene02 = std::make_unique<dae::GameObject>();
		auto logo = std::make_unique<dae::RenderComponent>(scene02.get());
		logo->SetTexture("logo.png");
		logo->SetPosition(358, 180);
		scene02->AddComponent(std::move(logo));
		scene.Add(std::move(scene02));

		//title assignment
		auto textObject = std::make_unique<dae::GameObject>();

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto textTitleComponent = std::make_unique<dae::TextComponent>(textObject.get(), "Programming 4 Assignment", font); //don't need this component ref anymore, so no need to safe the id
		textTitleComponent->SetColor({ 255, 255, 0, 255 });
		textTitleComponent->SetPosition(292, 20);
		textObject->AddComponent(std::move(textTitleComponent));

		auto textRenderer = std::make_unique<dae::RenderComponent>(textObject.get());
		textObject->AddComponent(std::move(textRenderer));	//everything that wants to get rendered (like text) needs a render component!
		scene.Add(std::move(textObject));

		//----controls------
		auto ControlsTextObject = std::make_unique<dae::GameObject>();

		auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
		auto textControllerComponent = std::make_unique<dae::TextComponent>(ControlsTextObject.get(), "Use D-Pad to move HotDogMan, X to inflict damage, and A to pick up pellets.", textFont); //don't need this component ref anymore, so no need to safe the id
		textControllerComponent->SetColor({ 255, 255, 255, 255 });
		textControllerComponent->SetPosition(10, 100);
		ControlsTextObject->AddComponent(std::move(textControllerComponent));

		auto textControllerRenderer = std::make_unique<dae::RenderComponent>(ControlsTextObject.get());
		ControlsTextObject->AddComponent(std::move(textControllerRenderer));	//everything that wants to get rendered (like text) needs a render component!
		scene.Add(std::move(ControlsTextObject));
		//-------------
		auto ControlsTextObject2 = std::make_unique<dae::GameObject>();

		auto textControllerComponent2 = std::make_unique<dae::TextComponent>(ControlsTextObject2.get(), "Use WASD to move Chef, Z to inflict damage, and X to pick up pellets. ", textFont);
		textControllerComponent2->SetColor({ 255, 255, 255, 255 });
		textControllerComponent2->SetPosition(10, 130);
		ControlsTextObject2->AddComponent(std::move(textControllerComponent2));

		auto textControllerRenderer2 = std::make_unique<dae::RenderComponent>(ControlsTextObject2.get());
		ControlsTextObject2->AddComponent(std::move(textControllerRenderer2));
		scene.Add(std::move(ControlsTextObject2));

		//-----end controlls-----

		//add fps component -> has on it's own: 
		auto fpsObject = std::make_unique<dae::GameObject>();

		auto fpsComp = std::make_unique<dae::FPSComponent>(fpsObject.get());
		auto textComp = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS: 0", font);
		auto textRenderer2 = std::make_unique<dae::RenderComponent>(fpsObject.get());

		fpsObject->AddComponent(std::move(textRenderer2));
		fpsObject->AddComponent(std::move(textComp));
		fpsObject->AddComponent(std::move(fpsComp));
		scene.Add(std::move(fpsObject));

		//----------------Players------------------------

		auto cook = std::make_unique<dae::GameObject>();
		auto picture = std::make_unique<dae::RenderComponent>(cook.get());
		picture->SetTexture("ForwardCook.png");
		picture->SetPosition(300, 300);
		cook->AddComponent(std::move(picture));

		//adding health component
		auto HealthComponent = std::make_unique<dae::HealthComponent>(cook.get(), 3);
		cook->AddComponent(std::move(HealthComponent));


		float cookSpeed{ 9600.f };
		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Up, cookSpeed))
			, SDL_SCANCODE_W, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Down, cookSpeed)),
			SDL_SCANCODE_S, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Left, cookSpeed)),
			SDL_SCANCODE_A, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Right, cookSpeed)),
			SDL_SCANCODE_D, InputState::Pressed);


		//----------------------hotdog man---------------------------------------
		auto hotdog = std::make_unique<dae::GameObject>();
		auto picture2 = std::make_unique<dae::RenderComponent>(hotdog.get());
		picture2->SetTexture("ForwardHotDog.png");
		picture2->SetPosition(360, 360);
		hotdog->AddComponent(std::move(picture2));


		float HotdogSpeed{ 15600.f };
		inputManager.GetControllerInput(0)->AddBinding(
			(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Up, HotdogSpeed)),
			ControllerInputs::DPAD_UP, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Down, HotdogSpeed)),
			ControllerInputs::DPAD_DOWN, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Left, HotdogSpeed)),
			ControllerInputs::DPAD_LEFT, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Right, HotdogSpeed)),
			ControllerInputs::DPAD_RIGHT, InputState::Pressed);

		scene.Add(std::move(hotdog));

		//--------------health output 01--------------------------
		auto TextOutputHealth = std::make_unique<dae::GameObject>();


		//-----------------the health renderer should be a different object to begin with---------------------------
		// 
		auto HealthOutput1Renderer = std::make_unique<dae::RenderComponent>(TextOutputHealth.get());
		TextOutputHealth->AddComponent(std::move(HealthOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!

		auto textHealth = std::make_unique<dae::TextComponent>(TextOutputHealth.get(), std::string("Amount Lives: 3"), textFont); //don't need this component ref anymore, so no need to safe the id
		textHealth->SetColor({ 255, 255, 255, 255 });
		textHealth->SetPosition(20, 300);
		TextOutputHealth->AddComponent(std::move(textHealth));


		//MAKING OBSERVERS AND CONNECTING THEM!!!!!!!
		auto healthObserver = std::make_unique<GameEvent>(TextOutputHealth.get());
		dae::ObserverManager::GetInstance().AddObserver(cook.get(), std::move(healthObserver));

		scene.Add(std::move(TextOutputHealth));
		//-----------------------------------------------------------------------------

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::HealthCommand>(cook.get(), -1)),
			SDL_SCANCODE_X, InputState::JustPressed); //should be justpressed or just released BOTH DONT WORK YET

		scene.Add(std::move(cook));
	}
}


