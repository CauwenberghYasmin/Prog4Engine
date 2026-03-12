#pragma once

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};


class GameObject;
class GameObjectCommand : public Command
{
	GameObject* m_GameObject; //make a GameActor class -> are gameobjects righttt
protected:
	GameObject* GetGameObject() const { return m_GameObject;}
public:
	GameObjectCommand(GameObject* actor);//constructor
	virtual ~GameObjectCommand();//don't delete -> does not own the pointer!

};

class MoveCommand : public GameObjectCommand {
public:
	void Execute() override
	{
		// GetGameActor()->move();
	}
};

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



class SprayCommand : public GameObjectCommand {
public:
	void Execute() override 
	{ 
		//GetGameActor()->Spray(); //put in cpp file so can include the h file
	} 
};



