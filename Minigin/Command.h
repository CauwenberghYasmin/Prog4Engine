#pragma once
#include "glm/vec2.hpp"
//go  over inheritance notes again to make sure!! (virtual, etc...)
#include "Game.h"
#include <vector>
#include <utility>
#include <string>

namespace dae {
	enum Direction {Up, Down, Left, Right};

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};


	class GameObject;
	class GameObjectCommand : public Command
	{
	protected:
		GameObject* m_GameObject; //cache object that calls it!
		[[nodiscard]] GameObject* GetGameObject() const { return m_GameObject; }

	public:
		explicit GameObjectCommand(GameObject* pGameObject);
		virtual ~GameObjectCommand() = default; //don't delete -> does not own the pointer!
	};



	class MoveCommand : public GameObjectCommand {
	public:

		explicit MoveCommand(GameObject* pGameObject, Direction direction, float speed);
		//don't make own destructor if not necessairy!

		void Execute() override; //implement code from the moveComponent (is deleted now)
		void SetSpeed(float newSpeed) { m_Speed = newSpeed; } //sprint in game?


	private:
		Direction m_Direction{};
		float m_Speed{}; //not const yet, should find way to change it!
		//don't cache gameObject again, it'a already saved in parent class
	};


	class ArrowMoveCommand : public GameObjectCommand {
	public:

		explicit ArrowMoveCommand(GameObject* pGameObject, Direction direction, float space, int amount);
		void Execute() override; //implement code from the moveComponent (is deleted now)

	private:
		Direction m_Direction;
		const float m_JumpBlocks;
		const int m_RowAmount;

		float m_MinPosY;
		float m_MaxPosY;
	};


	class SetGameModeCommand : public GameObjectCommand {
	public:

		SetGameModeCommand(GameObject* pGameObject, Game* game, std::vector<std::pair<float, Game::GameMode>> modeMappings); //pass game instance? (this)
		void Execute() override; // use game instance to set the game mode + go to the first level
		//dae::SceneManager::GetInstance().SetScene("Level01");

	private:
		Game* m_Game;
		std::vector<std::pair<float, Game::GameMode>> m_ModeMappings;
		//vector pair (y pos, GameMode::mode) gamemode passed from base class (or Game)

	};


	class HealthComponent;
	class HealthCommand : public GameObjectCommand {
	public:

		explicit HealthCommand(GameObject* pGameObject, int ChangeHealthAmount); //add neg for damage, pos for heal!
		void Execute() override; //implement code from the moveComponent (is deleted now)

	private:
		int m_AmountHealthChange{};
		HealthComponent* m_ObjectsHealthComponent{};
	};


	class SkipLevelCommand : public GameObjectCommand {
	public:

		explicit SkipLevelCommand(GameObject* pGameObject, std::vector<std::string> levelNames );
		void Execute() override;

	private:
		std::vector<std::string> m_LevelNames;
		int m_Index{0};
	};

	class MuteSoundCommand : public GameObjectCommand {
	public:

		explicit MuteSoundCommand(GameObject* pGameObject = nullptr);
		void Execute() override;
	};

	class ScoreComponent;
	class ScoreCommand : public GameObjectCommand {
	public:

		explicit ScoreCommand(GameObject* pGameObject, int ChangeScorePoints); //add neg for damage, pos for heal!
		void Execute() override; //implement code from the moveComponent (is deleted now)

	private:
		int m_AmountScoreChange{};
		ScoreComponent* m_ObjectsScoreComponent;
	};





	class SprayCommand : public GameObjectCommand {
	public:

		explicit SprayCommand(GameObject* pGameObject);
		void Execute() override;
	};


}
