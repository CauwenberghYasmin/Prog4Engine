#include "Command.h"
#include "GameTime.h"
#include "GameObject.h"


namespace dae {



	//constructor base class -> derive from it an dcall the base constructor!
	GameObjectCommand::GameObjectCommand(GameObject* pGameObject) :
		m_GameObject{ pGameObject }
	{
	}

	MoveCommand::MoveCommand(GameObject* pGameObject, Direction direction, float speed) :
		GameObjectCommand(pGameObject), m_Direction (direction), m_Speed(speed)
	{
	}

	SprayCommand::SprayCommand(GameObject* pGameObject) :
		GameObjectCommand(pGameObject)
	{
	}



	void MoveCommand::Execute() //how to I pass the direction enum??
	{
		glm::vec3 displacementVector{ 0,0,0 };
		float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

		switch (m_Direction) //game only requires straight up, down, left and right. no circle movement behaviours!
		{
		case Direction::Left:
			displacementVector.x -= m_Speed * deltaTime; //look into normalized value * speed or smth
			break;
		case Direction::Right:
			displacementVector.x += m_Speed * deltaTime; //maybe use geometric algebra from class!!!
			break;
		case Direction::Up:
			displacementVector.y -= m_Speed * deltaTime;
			break;
		case Direction::Down:
			displacementVector.y += m_Speed * deltaTime;
			break;
		}

		m_GameObject->SetLocalPosition(m_GameObject->GetLocalPosition() + (displacementVector * deltaTime));
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