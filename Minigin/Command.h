#pragma once

//go  over inheritance notes again to make sure!! (virtual, etc...)

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
		GameObject* GetGameObject() const { return m_GameObject; }
	public:
		explicit GameObjectCommand(GameObject* pGameObject);
		virtual ~GameObjectCommand() = default;//don't delete -> does not own the pointer!
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




	class SprayCommand : public GameObjectCommand {
	public:

		explicit SprayCommand(GameObject* pGameObject);
		void Execute() override;
	};


}
