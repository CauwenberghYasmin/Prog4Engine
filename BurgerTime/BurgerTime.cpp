#include "BurgerTime.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "Game.h"
#include "FpsComponent.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include <filesystem>
#include "InputManager.h"
#include "InputOptions.h"
#include "Command.h"
#include "KeyboardInput.h"
#include <string>
#include "ObserverManager.h"
#include "Observer.h"
#include "ServiceLocator.h"
#include "SdlSoundSystem.h"
#include "LoggingSoundSystem.h"
#include "SoundSystem.h"
#include "ReadLevelFile.h"
#include "CollisionComponent.h"
#include "Scene.h"
#include <iostream>

enum Direction { Up, Down, Left, Right };
void colFuncTemp(CollisionComponent* coll); //DELETE TEMP

namespace fs = std::filesystem;
namespace dae {

	void LoadLevel01(Scene* scene);

	BurgerTime::BurgerTime() :
		Game()
	{
	}

	BurgerTime::~BurgerTime() = default;

	
	void BurgerTime::Initialize() //0,0 IS TOP LEFT CORNER
	{
		#if _DEBUG
			dae::ServiceLocator::register_sound_system(std::make_unique<sdl_sound_system>());
			//ServiceLocator::register_sound_system(std::make_unique<logging_sound_system>(std::make_unique<sdl_sound_system>()));
		#else
			dae::ServiceLocator::register_sound_system(std::make_unique<sdl_sound_system>());
		#endif

		sdl_sound_system& soundSystem = dynamic_cast<sdl_sound_system&>(ServiceLocator::get_sound_system());
		soundSystem.RegisterSound(1, "Data/sounds/bubbels.wav");


		//CHANGE HERE SO MAKE SENSE
		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->LoadStartScreen(s);
		},
		"StartScreen" );

		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->PracticeScene(s);
		},
		"PracticeScene" );

		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->LoadLevel01(s);
		},
		"Level01" ); //USE LAMBDA BECAUSE OF THIS POINTER

		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->LoadLevel02(s);
		},
		"Level02" );

		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->LoadLevel03(s);
		},
		"Level03" );


		dae::SceneManager::GetInstance().SetScene("StartScreen");


	//add binding to skip levels
	//add binding to mute and unmute


	}
	//-> initialize the start screen
	//call here functions to create scene2, 3, and att things + change current scene in the scene manager

	void BurgerTime::LoadStartScreen(Scene* scene) {

		auto& inputManager = dae::InputManager::GetInstance(); //make binding for the arrows

		auto backgroundObj = std::make_unique<dae::GameObject>();
		auto background = std::make_unique<dae::RenderComponent>(backgroundObj.get());
		background->SetTexture("StartScreen.png");
		backgroundObj->AddComponent(std::move(background));
		scene->Add(std::move(backgroundObj));

		auto arrow = std::make_unique<dae::GameObject>();
		auto arrowPic = std::make_unique<dae::RenderComponent>(arrow.get());
		arrowPic->SetTexture("Arrow.png");
		arrowPic->SetPosition(329, 471);
		arrow->AddComponent(std::move(arrowPic));

		constexpr float jumpAmount {50.f};
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::ArrowMoveCommand>(arrow.get(), dae::Direction::Up, jumpAmount, 3))
			, SDL_SCANCODE_W, InputState::JustReleased);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::ArrowMoveCommand>(arrow.get(), dae::Direction::Down, jumpAmount, 3)),
			SDL_SCANCODE_S, InputState::JustReleased);

		const float yposStart {471};
		auto vec = std::vector<std::pair<float, GameMode>>();
		vec.emplace_back((std::pair<float, GameMode>{ yposStart, GameMode::single })); //std::move makes no difference here: trivial copyable
		vec.emplace_back((std::pair<float, GameMode>{ yposStart + jumpAmount, GameMode::Coop }));
		vec.emplace_back((std::pair<float, GameMode>{ yposStart + jumpAmount*2, GameMode::VS }));

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::SetGameModeCommand>(arrow.get(), dynamic_cast<Game*>(this), std::move(vec))),
			SDL_SCANCODE_X, InputState::JustReleased);


		//once pressed diff binding (x) -> undo bindings and go to new level + set game mode

		//bindings  mute (NOT TO SKIP LEVEL, HAVENT PICKED AN INSTANCE YET)

		scene->Add(std::move(arrow));

	}

	void BurgerTime::LoadLevel01(Scene* scene) {
		ReadLevelFile::LoadlevelFromFile(*scene, "Data/levelFiles/Level01.txt");

		auto& inputManager = dae::InputManager::GetInstance();
		//inputManager.GetKeyboardInput()->RemoveBinding()

		//-----------------SKIP LEVELS BINDINGS && MUTE----------------------------------
		auto vecLevelNames = std::vector<std::string>();
		vecLevelNames.emplace_back("Level01");
		vecLevelNames.emplace_back("Level02");
		vecLevelNames.emplace_back("Level03");

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::SkipLevelCommand>(nullptr, std::move(vecLevelNames))),
			SDL_SCANCODE_F1, InputState::JustReleased);

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::MuteSoundCommand>(nullptr)),
			SDL_SCANCODE_F2, InputState::JustReleased);
		//----------------------------------------------------------------------

		//------------------------------COOK---------------------------------------
	 	auto cook = std::make_unique<dae::GameObject>();
	 	cook->Tag = "Player";
		auto picture = std::make_unique<dae::RenderComponent>(cook.get());
		picture->SetTexture("Cook.png");
		picture->SetPosition(320, 320);
		const glm::vec2 picSize = picture->GetTextureSize();
		cook->AddComponent(std::move(picture));

		//adding health component
		auto HealthComponent = std::make_unique<dae::HealthComponent>(cook.get(), 4);
		cook->AddComponent(std::move(HealthComponent));

	 	//coll behaviour + comp
		auto collBeh = std::make_unique<CookCollisionBehaviours>(cook.get());
		cook->AddComponent(std::move(collBeh));
		auto CollComp = std::make_unique<CollisionComponent>(cook.get(), false, 1);
		CollComp->SetCollisionBox(picSize.x, picSize.y/2, CollisionComponent::Alignment::Bottom);
		cook ->AddComponent(std::move(CollComp));

	 	//------------------------------player inputs------------------------------------
		float cookSpeed{ 100.f };
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Up, cookSpeed))
			, SDL_SCANCODE_W, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Down, cookSpeed)),
			SDL_SCANCODE_S, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Left, cookSpeed)),
			SDL_SCANCODE_A, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Right, cookSpeed)),
			SDL_SCANCODE_D, InputState::Pressed);

		//---------------------------CONNECT HEALTH---------------------------------

		auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
		auto TextOutputHealth = std::make_unique<dae::GameObject>();
		auto HealthOutput1Renderer = std::make_unique<dae::RenderComponent>(TextOutputHealth.get());
		TextOutputHealth->AddComponent(std::move(HealthOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!

		auto textHealth = std::make_unique<dae::TextComponent>(TextOutputHealth.get(), std::string("Amount Lives: 4"), textFont); //don't need this component ref anymore, so no need to safe the id
		textHealth->SetColor({ 255, 255, 255, 255 });
		textHealth->SetPosition(20, 20);
		TextOutputHealth->AddComponent(std::move(textHealth));

		auto healthObserver = std::make_unique<GameEvent>(TextOutputHealth.get());
		dae::ObserverManager::GetInstance().AddObserver(cook.get(), std::move(healthObserver));
		scene->Add(std::move(TextOutputHealth));

		//--------------------------------------------------------------------------------------------------

	 	scene->Add(std::move(cook));
		// -------------------------------------------------------------------------------------------------------------------------

		if (currGameMode == GameMode::Coop) {
			//create second player
			auto cook2 = std::make_unique<dae::GameObject>();
			cook2->Tag = "Player";
			auto picture2 = std::make_unique<dae::RenderComponent>(cook2.get());
			picture2->SetTexture("Cook2.png");
			picture2->SetPosition(220, 320);
			cook2->AddComponent(std::move(picture2));

			//adding health component
			auto HealthComponent2 = std::make_unique<dae::HealthComponent>(cook2.get(), 3);
			cook2->AddComponent(std::move(HealthComponent2));

			//coll behaviour + comp
			auto collBeh2 = std::make_unique<CookCollisionBehaviours>(cook2.get());	//CREATE BEFORE COLLCOMP
			cook2->AddComponent(std::move(collBeh2));
			auto CollComp2 = std::make_unique<CollisionComponent>(cook2.get(), false, 1); // Changed 'true' to an int ID
			CollComp2->SetCollisionBox(picSize.x, picSize.y/2, CollisionComponent::Alignment::Bottom);
			cook2 ->AddComponent(std::move(CollComp2)); //SET FUNCTION DONE IN COLLBEH

			//player inputs
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Up, cookSpeed))
				, SDL_SCANCODE_UP, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Down, cookSpeed)),
				SDL_SCANCODE_DOWN, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Left, cookSpeed)),
				SDL_SCANCODE_LEFT, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Right, cookSpeed)),
				SDL_SCANCODE_RIGHT, InputState::Pressed);
			scene->Add(std::move(cook2));
		}

		if (currGameMode == GameMode::VS) {
			auto HotDogPlayer = std::make_unique<dae::GameObject>();
			HotDogPlayer->Tag = "Enemy";
			auto picture2 = std::make_unique<dae::RenderComponent>(HotDogPlayer.get());
			picture2->SetTexture("HotDog.png");
			picture2->SetPosition(220, 320);
			HotDogPlayer->AddComponent(std::move(picture2));

			//coll behaviour + comp
			auto collBeh2 = std::make_unique<CookCollisionBehaviours>(HotDogPlayer.get());	//CREATE BEFORE COLLCOMP
			HotDogPlayer->AddComponent(std::move(collBeh2));
			auto CollComp2 = std::make_unique<CollisionComponent>(HotDogPlayer.get(), false, 1); // Changed 'true' to an int ID
			CollComp2->SetCollisionBox(picSize.x, picSize.y/2, CollisionComponent::Alignment::Bottom);
			HotDogPlayer ->AddComponent(std::move(CollComp2)); //SET FUNCTION DONE IN COLLBEH

			//player inputs
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Up, cookSpeed))
				, SDL_SCANCODE_UP, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Down, cookSpeed)),
				SDL_SCANCODE_DOWN, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Left, cookSpeed)),
				SDL_SCANCODE_LEFT, InputState::Pressed);
			inputManager.GetKeyboardInput()->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Right, cookSpeed)),
				SDL_SCANCODE_RIGHT, InputState::Pressed);
			scene->Add(std::move(HotDogPlayer));
		}
	}

	void BurgerTime::LoadLevel02(Scene* scene) {
		ReadLevelFile::LoadlevelFromFile(*scene, "Data/levelFiles/Level02.txt");
	}

	void BurgerTime::LoadLevel03(Scene* scene) {
		ReadLevelFile::LoadlevelFromFile(*scene, "Data/levelFiles/Level03.txt");
		//only this level needs box colliders so the chef doesn't fall off!!!!
	}



	void BurgerTime::PracticeScene(Scene* scene)
	{ //add BurgerTime::!!!!
		//has everything we made at the beginning!!
		auto& inputManager = dae::InputManager::GetInstance();
		//-----------------------------------------------------------------------------
		//auto scene01 = std::make_unique<dae::GameObject>();
		//auto background = std::make_unique<dae::RenderComponent>(scene01.get());
		//background->SetTexture("background.png");
		//scene01->AddComponent(std::move(background));
		//scene.Add(std::move(scene01));


		//auto scene02 = std::make_unique<dae::GameObject>();
		//auto logo = std::make_unique<dae::RenderComponent>(scene02.get());
		//logo->SetTexture("logo.png");
		//logo->SetPosition(358, 180);
		//scene02->AddComponent(std::move(logo));
		//scene.Add(std::move(scene02));

		//title assignment
		//auto textObject = std::make_unique<dae::GameObject>();

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		//auto textTitleComponent = std::make_unique<dae::TextComponent>(textObject.get(), "Programming 4 Assignment", font); //don't need this component ref anymore, so no need to safe the id
		//textTitleComponent->SetColor({ 255, 255, 0, 255 });
		//textTitleComponent->SetPosition(292, 20);
		//textObject->AddComponent(std::move(textTitleComponent));

		//auto textRenderer = std::make_unique<dae::RenderComponent>(textObject.get());
		//textObject->AddComponent(std::move(textRenderer));	//everything that wants to get rendered (like text) needs a render component!
		//scene.Add(std::move(textObject));

		//----controls------
		auto ControlsTextObject = std::make_unique<dae::GameObject>();

		auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
		auto textControllerComponent = std::make_unique<dae::TextComponent>(ControlsTextObject.get(), "Use D-Pad to move HotDogMan, X to inflict damage, and A to pick up pellets.", textFont); //don't need this component ref anymore, so no need to safe the id
		textControllerComponent->SetColor({ 255, 255, 255, 255 });
		textControllerComponent->SetPosition(10, 100);
		ControlsTextObject->AddComponent(std::move(textControllerComponent));

		auto textControllerRenderer = std::make_unique<dae::RenderComponent>(ControlsTextObject.get());
		ControlsTextObject->AddComponent(std::move(textControllerRenderer));	//everything that wants to get rendered (like text) needs a render component!
		//scene.Add(std::move(ControlsTextObject));
		//-------------
		auto ControlsTextObject2 = std::make_unique<dae::GameObject>();

		auto textControllerComponent2 = std::make_unique<dae::TextComponent>(ControlsTextObject2.get(), "Use WASD to move Chef, Z to inflict damage, and X to pick up pellets. ", textFont);
		textControllerComponent2->SetColor({ 255, 255, 255, 255 });
		textControllerComponent2->SetPosition(10, 130);
		ControlsTextObject2->AddComponent(std::move(textControllerComponent2));

		auto textControllerRenderer2 = std::make_unique<dae::RenderComponent>(ControlsTextObject2.get());
		ControlsTextObject2->AddComponent(std::move(textControllerRenderer2));
		//scene.Add(std::move(ControlsTextObject2));

		//-----end controlls-----

		//add fps component -> has on it's own:
		auto fpsObject = std::make_unique<dae::GameObject>();

		auto fpsComp = std::make_unique<dae::FPSComponent>(fpsObject.get());
		auto textComp = std::make_unique<dae::TextComponent>(fpsObject.get(), "FPS: 0", font);
		auto textRenderer2 = std::make_unique<dae::RenderComponent>(fpsObject.get());

		fpsObject->AddComponent(std::move(textRenderer2));
		fpsObject->AddComponent(std::move(textComp));
		fpsObject->AddComponent(std::move(fpsComp));
		//scene.Add(std::move(fpsObject));

		//----------------Players------------------------

		auto cook = std::make_unique<dae::GameObject>();
		auto picture = std::make_unique<dae::RenderComponent>(cook.get());
		picture->SetTexture("ForwardCook.png");
		picture->SetPosition(320, 320);
		cook->AddComponent(std::move(picture));

		//adding health component
		auto HealthComponent = std::make_unique<dae::HealthComponent>(cook.get(), 3);
		cook->AddComponent(std::move(HealthComponent));




		auto collBeh = std::make_unique<CookCollisionBehaviours>(cook.get());	//CREATE BEFORE COLLCOMP
		cook->AddComponent(std::move(collBeh));

		auto CollComp = std::make_unique<CollisionComponent>(cook.get(), false, 1); // Changed 'true' to an int ID
		cook ->AddComponent(std::move(CollComp)); //SET FUNCTION DONE IN COLLBEH

		cook->Tag = "Player";

		float cookSpeed{ 9600.f };
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Up, cookSpeed))
			, SDL_SCANCODE_W, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Down, cookSpeed)),
			SDL_SCANCODE_S, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Left, cookSpeed)),
			SDL_SCANCODE_A, InputState::Pressed);
		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Right, cookSpeed)),
			SDL_SCANCODE_D, InputState::Pressed);



		//----------------------hotdog man---------------------------------------
		auto hotdog = std::make_unique<dae::GameObject>();
		auto picture2 = std::make_unique<dae::RenderComponent>(hotdog.get());
		picture2->SetTexture("ForwardHotDog.png");
		picture2->SetPosition(360, 360);
		hotdog->AddComponent(std::move(picture2));
		hotdog->Tag = "Enemy";
		auto coll = std::make_unique<CollisionComponent>(hotdog.get(), false, 1);
		hotdog->AddComponent(std::move(coll));


		float HotdogSpeed{ 15600.f };
		inputManager.GetControllerInput(0)->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Up, HotdogSpeed)),
			ControllerInputs::DPAD_UP, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Down, HotdogSpeed)),
			ControllerInputs::DPAD_DOWN, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Left, HotdogSpeed)),
			ControllerInputs::DPAD_LEFT, InputState::Pressed);
		inputManager.GetControllerInput(0)->AddBinding(
			std::move(std::make_unique<dae::MoveCommand>(hotdog.get(), dae::Direction::Right, HotdogSpeed)),
			ControllerInputs::DPAD_RIGHT, InputState::Pressed);

		scene->Add(std::move(hotdog));

		//-------------------health output 01--------------------------


		//-----------------the health renderer should be a different object to begin with---------------------------
		//

		auto TextOutputHealth = std::make_unique<dae::GameObject>();
		auto HealthOutput1Renderer = std::make_unique<dae::RenderComponent>(TextOutputHealth.get());
		TextOutputHealth->AddComponent(std::move(HealthOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!

		auto textHealth = std::make_unique<dae::TextComponent>(TextOutputHealth.get(), std::string("Amount Lives: 4"), textFont); //don't need this component ref anymore, so no need to safe the id
		textHealth->SetColor({ 255, 255, 255, 255 });
		textHealth->SetPosition(20, 300);
		TextOutputHealth->AddComponent(std::move(textHealth));

		auto healthObserver = std::make_unique<GameEvent>(TextOutputHealth.get());
		dae::ObserverManager::GetInstance().AddObserver(cook.get(), std::move(healthObserver));
		scene->Add(std::move(TextOutputHealth));


		//-----------------------------------------------------------------------------

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::HealthCommand>(cook.get(), -1)),
			SDL_SCANCODE_X, InputState::JustPressed);

		inputManager.GetKeyboardInput()->AddBinding(
			(std::make_unique<dae::HealthCommand>(cook.get(), -1)),
			SDL_SCANCODE_Z, InputState::JustPressed); //should be justpressed or just released BOTH DONT WORK YET

		scene->Add(std::move(cook));


		//FOR COOK:
		// playerCollisionComp->SetFunction([](CollisionComponent* other)
		// {
		// 	// The player handles the reaction based on WHO they hit
		// 	std::string tag = other->GetOwnerTag();
		//
		// 	if (tag == "Tile_Walkable")
		// 	{
		//
		// 	}
		// 	else if (tag == "Tile_Lava")
		// 	{
		//
		// 	}
		// }, CollisionComponent::CollisionType::OnEnter);


	}

	void colFuncTemp(CollisionComponent* coll) {
		auto* OtherGameObject = coll->GetOwner();

		if (OtherGameObject->Tag == "Enemy") {
			ServiceLocator::get_sound_system().PlaySound(1, 50);
		}
	}
}


