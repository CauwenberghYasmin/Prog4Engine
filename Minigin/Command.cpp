#include "Command.h"
#include "GameTime.h"
#include "GameObject.h"


namespace dae {



	//constructor base class -> derive from it an dcall the base constructor!
	GameObjectCommand::GameObjectCommand(GameObject* pGameObject) :
		m_GameObject{ pGameObject }
	{
	}

	MoveCommand::MoveCommand(GameObject* pGameObject) :
		GameObjectCommand(pGameObject)
	{
	}

	SprayCommand::SprayCommand(GameObject* pGameObject) :
		GameObjectCommand(pGameObject)
	{
	}



	void MoveCommand::Execute() //how to I pass the direction enum??
	{
		glm::vec3 m_Direction{ 0,0,0 };
		float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

		//switch (direction)
		//{
		//case Direction::Left:
		//	m_Direction.x -= m_MovementSpeed; //look into normalized value * speed or smth
		//	break;
		//case Direction::Right:
		//	m_Direction.x += m_MovementSpeed; //maybe use geometric algebra from class!!!
		//	break;
		//case Direction::Up:
		//	m_Direction.y -= m_MovementSpeed;
		//	break;
		//case Direction::Down:
		//	m_Direction.y += m_MovementSpeed;
		//	break;
		//}

		m_GameObject->SetLocalPosition(m_GameObject->GetLocalPosition() + (m_Direction * deltaTime));
	}

	void SprayCommand::Execute()
	{
		//GetGameActor()->Spray(); //put in cpp file so can include the h file

			//can spray in direction last looked (up/down/left/right)
			//show sparkle effect
			//look if sound effect..?
			//make somewhere a collision system so that the enemies know what they are hit
			//make counter of amount of sprays go down (event system?)
	}


}