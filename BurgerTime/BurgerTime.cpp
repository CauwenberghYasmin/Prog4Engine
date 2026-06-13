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
#include "PlayerStateComponent.h"
#include "EnemySpawner.h"
#include "Scene.h"
#include <iostream>

#include "Burger.h"
#include "PickUpSpawner.h"
#include "SprayAttackComponent.h"

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

		dae::SceneManager::GetInstance().CreateScene(
		[this](Scene* s) {
		this->LoadHighScore(s);
		},
		"HighScoreScene" );


		dae::SceneManager::GetInstance().SetScene("StartScreen");

		std::vector<std::string>vecLevelNames;
		vecLevelNames.emplace_back("Level01");
		vecLevelNames.emplace_back("Level02");
		vecLevelNames.emplace_back("Level03");
		LevelManager::GetInstance().Init(std::move(vecLevelNames));
	//add binding to skip levels
	//add binding to mute and unmute


	}
	//-> initialize the start screen
	//call here functions to create scene2, 3, and att things + change current scene in the scene manager

	void BurgerTime::LoadHighScore(Scene* scene) {
		//auto& inputManager = dae::InputManager::GetInstance(); //make binding for the arrows

		if (scene == nullptr) return;

		LevelManager::GetInstance().ResetGame();
		//background blac!



	}



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
		inputManager.GetKeyboardInput()->RemoveAllBindings(); //-> just put by every scene load or not??
		std::vector<GameObject*> players;
		SetupPlayersAndUI(scene, players);

		//--------------------------ENEMY SPAWNER-----------------------------
		std::vector<glm::vec2> positions{};
		const int enemyAmount{7};
		positions.reserve(enemyAmount);
		positions.emplace_back(699, 140);
		positions.emplace_back(90, 61);
		positions.emplace_back(104, 268);
		positions.emplace_back(103, 445);
		positions.emplace_back(904, 54);
		positions.emplace_back(904, 140);
		positions.emplace_back(901, 376);

		auto EnemySpawn = std::make_unique<dae::GameObject>();
		EnemySpawn->AddComponent(std::make_unique<EnemySpawner>(EnemySpawn.get(), players, positions, enemyAmount, scene));
		scene->Add(std::move(EnemySpawn));

		//-------------------ice cream spawner-----------------------------------

		std::vector<glm::vec2> posItem{};
		const int itemAmount{7};
		posItem.reserve(itemAmount);
		posItem.emplace_back(699, 140);
		posItem.emplace_back(90, 61);
		posItem.emplace_back(104, 268);
		posItem.emplace_back(103, 445);
		posItem.emplace_back(904, 54);
		posItem.emplace_back(904, 140);
		posItem.emplace_back(901, 376);

		auto Item = std::make_unique<dae::GameObject>();
		Item->AddComponent(std::make_unique<PickUpSpawner>(Item.get(), posItem, itemAmount, scene));
		auto gmObserver = std::make_unique<GameManagerObserver>();
		dae::ObserverManager::GetInstance().AddObserver(Item.get(), std::move(gmObserver));
		scene->Add(std::move(Item));

	}

	void BurgerTime::LoadLevel02(Scene* scene) {
		ReadLevelFile::LoadlevelFromFile(*scene, "Data/levelFiles/Level02.txt");
		auto& inputManager = dae::InputManager::GetInstance();
		inputManager.GetKeyboardInput()->RemoveAllBindings(); //-> just put by every scene load or not??
		std::vector<GameObject*> players;
		SetupPlayersAndUI(scene, players);

		//--------------------------ENEMY SPAWNER-----------------------------
		std::vector<glm::vec2> positions{};
		const int enemyAmount{7};
		positions.reserve(enemyAmount);
		positions.emplace_back(699, 140);
		positions.emplace_back(90, 61);
		positions.emplace_back(104, 268);
		positions.emplace_back(103, 445);
		positions.emplace_back(904, 54);
		positions.emplace_back(904, 140);
		positions.emplace_back(901, 376);

		auto EnemySpawn = std::make_unique<dae::GameObject>();
		EnemySpawn->AddComponent(std::make_unique<EnemySpawner>(EnemySpawn.get(), players, positions, enemyAmount, scene));
		scene->Add(std::move(EnemySpawn));

		//-------------------ice cream spawner-----------------------------------

		std::vector<glm::vec2> posItem{};
		const int itemAmount{7};
		posItem.reserve(itemAmount);
		posItem.emplace_back(699, 140);
		posItem.emplace_back(90, 61);
		posItem.emplace_back(104, 268);
		posItem.emplace_back(103, 445);
		posItem.emplace_back(904, 54);
		posItem.emplace_back(904, 140);
		posItem.emplace_back(901, 376);

		auto Item = std::make_unique<dae::GameObject>();
		Item->AddComponent(std::make_unique<PickUpSpawner>(Item.get(), posItem, itemAmount, scene));

		auto gmObserver = std::make_unique<GameManagerObserver>();
		dae::ObserverManager::GetInstance().AddObserver(Item.get(), std::move(gmObserver));
		scene->Add(std::move(Item));

	}

	void BurgerTime::LoadLevel03(Scene* scene) {
		ReadLevelFile::LoadlevelFromFile(*scene, "Data/levelFiles/Level03.txt");
		auto& inputManager = dae::InputManager::GetInstance();
		inputManager.GetKeyboardInput()->RemoveAllBindings(); //-> just put by every scene load or not??
		std::vector<GameObject*> players;
		SetupPlayersAndUI(scene, players);

		//--------------------------ENEMY SPAWNER-----------------------------
		std::vector<glm::vec2> positions{};
		const int enemyAmount{7};
		positions.reserve(enemyAmount);
		positions.emplace_back(699, 140);
		positions.emplace_back(90, 61);
		positions.emplace_back(104, 268);
		positions.emplace_back(103, 445);
		positions.emplace_back(904, 54);
		positions.emplace_back(904, 140);
		positions.emplace_back(901, 376);

		auto EnemySpawn = std::make_unique<dae::GameObject>();
		EnemySpawn->AddComponent(std::make_unique<EnemySpawner>(EnemySpawn.get(), players, positions, enemyAmount, scene));
		scene->Add(std::move(EnemySpawn));

		//-------------------ice cream spawner-----------------------------------

		std::vector<glm::vec2> posItem{};
		const int itemAmount{7};
		posItem.reserve(itemAmount);
		posItem.emplace_back(699, 140);
		posItem.emplace_back(90, 61);
		posItem.emplace_back(104, 268);
		posItem.emplace_back(103, 445);
		posItem.emplace_back(904, 54);
		posItem.emplace_back(904, 140);
		posItem.emplace_back(901, 376);

		auto Item = std::make_unique<dae::GameObject>();
		Item->AddComponent(std::make_unique<PickUpSpawner>(Item.get(), posItem, itemAmount, scene));
		auto gmObserver = std::make_unique<GameManagerObserver>();
		dae::ObserverManager::GetInstance().AddObserver(Item.get(), std::move(gmObserver));
		scene->Add(std::move(Item));

	}



	void BurgerTime::SetupPlayersAndUI(dae::Scene* scene, std::vector<GameObject*>& players)
	{
		auto& inputManager = dae::InputManager::GetInstance();
		inputManager.GetKeyboardInput()->RemoveAllBindings();
		inputManager.GetControllerInput(0)->RemoveAllBindings();
		inputManager.GetControllerInput(1)->RemoveAllBindings();
		players.clear();
		dae::ObserverManager::GetInstance().ClearAllObservers();

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

		//------------------------------COOK---------------------------------------
	 	auto cook = std::make_unique<dae::GameObject>();
	 	cook->Tag = "Player";
		auto picture = std::make_unique<dae::RenderComponent>(cook.get());
		picture->SetTexture("Cook.png");
		picture->SetPosition(320, 320);
		const glm::vec2 picSize = picture->GetTextureSize();
		cook->AddComponent(std::move(picture));
		auto playerState = std::make_unique<PlayerStateComponent>(cook.get());
		cook->AddComponent(std::move(playerState));

		//-------------------------SPRAY OBJECT - CHILD------------------------------------
		auto spray = std::make_unique<dae::GameObject>();

		spray->Tag = "Spray";
		auto pic = std::make_unique<dae::RenderComponent>(spray.get());
		pic->SetTexture("Spray.png");
		pic->SetPosition(24, 4);
		pic->m_IsRendering = false;
		spray->AddComponent(std::move(pic));
		auto collSpray = std::make_unique<CollisionComponent>(spray.get(), false);
		collSpray->m_IsCollisionOn = false;
		spray ->AddComponent(std::move(collSpray));
		spray->SetParent(cook.get(), false);


		cook->AddComponent(std::move(std::make_unique<SprayAttackComponent>(cook.get(), spray.get(), 5)));
		scene->Add(std::move(spray));
		//-------------------------------------------------------------------------------------

		//adding health component
		int currentLives = LevelManager::GetInstance().GetLives();
		auto HealthComponent = std::make_unique<dae::HealthComponent>(cook.get(), currentLives);
		cook->AddComponent(std::move(HealthComponent));

	 	//coll behaviour + comp
		auto collBeh = std::make_unique<CookCollisionBehaviours>(cook.get());
		cook->AddComponent(std::move(collBeh));
		auto CollComp = std::make_unique<CollisionComponent>(cook.get(), false, 1);
		CollComp->SetCollisionBox(picSize.x, picSize.y/2, CollisionComponent::Alignment::Bottom);
		cook ->AddComponent(std::move(CollComp));

	 	//------------------------------player inputs------------------------------------
		float cookSpeed{ 100.f };

		if (!m_GameStarted) {

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

		inputManager.GetKeyboardInput()->AddBinding(
			std::move(std::make_unique<dae::SprayCommand>(cook.get())),
			SDL_SCANCODE_Z, InputState::JustPressed);

			//WITH CONSOLE
			inputManager.GetControllerInput(0)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Up, cookSpeed))
				, ControllerInputs::DPAD_UP, InputState::Pressed);
			inputManager.GetControllerInput(0)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Down, cookSpeed)),
				ControllerInputs::DPAD_DOWN, InputState::Pressed);
			inputManager.GetControllerInput(0)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Left, cookSpeed)),
				ControllerInputs::DPAD_LEFT, InputState::Pressed);
			inputManager.GetControllerInput(0)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook.get(), dae::Direction::Right, cookSpeed)),
				ControllerInputs::DPAD_RIGHT, InputState::Pressed);

			inputManager.GetControllerInput(0)->AddBinding(
			std::move(std::make_unique<dae::SprayCommand>(cook.get())),
			ControllerInputs::BUTTON_X, InputState::JustPressed);
		}
		//---------------------------CONNECT HEALTH---------------------------------

		auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 21);
		auto TextOutputHealth = std::make_unique<dae::GameObject>();
		auto HealthOutput1Renderer = std::make_unique<dae::RenderComponent>(TextOutputHealth.get());
		TextOutputHealth->AddComponent(std::move(HealthOutput1Renderer));	//everything that wants to get rendered (like text) needs a render component!

		auto textHealth = std::make_unique<dae::TextComponent>(TextOutputHealth.get(), std::string("Amount Lives:" + std::to_string(currentLives)), textFont); //don't need this component ref anymore, so no need to safe the id
		textHealth->SetColor({ 255, 255, 255, 255 });
		textHealth->SetPosition(20, 20);
		TextOutputHealth->AddComponent(std::move(textHealth));

		auto healthObserver = std::make_unique<GameEvent>(TextOutputHealth.get());
		dae::ObserverManager::GetInstance().AddObserver(cook.get(), std::move(healthObserver));
		scene->Add(std::move(TextOutputHealth));

		// int currentScore = LevelManager::GetInstance().GetScore();
		// auto scoreTextObj = std::make_unique<dae::GameObject>();
		// auto scoreRenderer = std::make_unique<dae::RenderComponent>(scoreTextObj.get());
		// scoreTextObj->AddComponent(std::move(scoreRenderer));
		// auto textScore = std::make_unique<dae::TextComponent>(scoreTextObj.get(), "Score: " + std::to_string(currentScore), textFont);
		// textScore->SetColor({ 255, 255, 255, 255 });
		// textScore->SetPosition(20, 50);
		// scoreTextObj->AddComponent(std::move(textScore));

		//auto scoreObserver = std::make_unique<GameEvent>(scoreTextObj.get());
		//dae::ObserverManager::GetInstance().AddObserver(cook.get(), std::move(scoreObserver));
		//scene->Add(std::move(scoreTextObj));	//NOT WORKING

		//--------------------------------------------------------------------------------------------------
		players.emplace_back(cook.get()); //fake error
	 	scene->Add(std::move(cook));

		// ------------------------------------------------DIFF GAME MODES-------------------------------------------------------------------------
		if (currGameMode == GameMode::Coop) {
			//create second player
			auto cook2 = std::make_unique<dae::GameObject>();
			cook2->Tag = "Player";
			auto picture2 = std::make_unique<dae::RenderComponent>(cook2.get());
			picture2->SetTexture("Cook2.png");
			picture2->SetPosition(220, 320);
			cook2->AddComponent(std::move(picture2));

			//adding health component
			auto HealthComponent2 = std::make_unique<dae::HealthComponent>(cook2.get(), currentLives);
			cook2->AddComponent(std::move(HealthComponent2));

			//coll behaviour + comp
			auto collBeh2 = std::make_unique<CookCollisionBehaviours>(cook2.get());	//CREATE BEFORE COLLCOMP
			cook2->AddComponent(std::move(collBeh2));
			auto CollComp2 = std::make_unique<CollisionComponent>(cook2.get(), false, 1); // Changed 'true' to an int ID
			CollComp2->SetCollisionBox(picSize.x, picSize.y/2, CollisionComponent::Alignment::Bottom);
			cook2 ->AddComponent(std::move(CollComp2)); //SET FUNCTION DONE IN COLLBEH

			//player inputs controller 2
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Up, cookSpeed))
				, ControllerInputs::DPAD_UP, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Down, cookSpeed)),
				ControllerInputs::DPAD_DOWN, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Left, cookSpeed)),
				ControllerInputs::DPAD_LEFT, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(cook2.get(), dae::Direction::Right, cookSpeed)),
				ControllerInputs::DPAD_RIGHT, InputState::Pressed);

			players.emplace_back(cook2.get());
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
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Up, cookSpeed))
				, ControllerInputs::DPAD_UP, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Down, cookSpeed)),
				ControllerInputs::DPAD_DOWN, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Left, cookSpeed)),
				ControllerInputs::DPAD_LEFT, InputState::Pressed);
			inputManager.GetControllerInput(1)->AddBinding(
				std::move(std::make_unique<dae::MoveCommand>(HotDogPlayer.get(), dae::Direction::Right, cookSpeed)),
				ControllerInputs::DPAD_RIGHT, InputState::Pressed);
			scene->Add(std::move(HotDogPlayer));
		}
	}







}


