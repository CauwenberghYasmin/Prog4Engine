#include "Command.h"
#include "GameObject.h"

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


void MoveCommand::Execute()
{

// move this code to the movementCommand
//float deltaTime = dae::GameTime::GetInstance().GetDeltaTime(); -> safe this somewhere in class (or best to recalc every frame? -> look up!)

//void dae::MovementComponent::Update()
//{
//
//	if (m_ShouldMove) //look into replacing with the event system!!
//	{
//		GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition() + (m_Direction * deltaTime));
//		m_Direction = glm::vec3{ 0,0,0 }; //reset after movement is done!
//		m_ShouldMove = false;
//	}
//}

//void dae::MovementComponent::Move(Direction direction)
//{
//	switch (direction)
//	{
//	case Direction::Left:
//		m_Direction.x -= m_MovementSpeed; //look into normalized value * speed or smth
//		break;
//	case Direction::Right:
//		m_Direction.x += m_MovementSpeed; //maybe use geometric algebra from class!!!
//		break;
//	case Direction::Up:
//		m_Direction.y -= m_MovementSpeed;
//		break;
//	case Direction::Down:
//		m_Direction.y += m_MovementSpeed;
//		break;
//	}
//
//	m_ShouldMove = true;
//}

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
