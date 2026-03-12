#include "MovementComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Component.h"
#include <glm/glm.hpp>

using namespace dae;

MovementComponent::MovementComponent(GameObject* pGameObject, int id, float movementSpeed):
	Component(pGameObject, id), m_MovementSpeed{ movementSpeed }
{
}

void dae::MovementComponent::Update()
{

	if (m_ShouldMove) //only updates when movement is needed!
	{
		float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
		GetOwner()->SetLocalPosition(GetOwner()->GetLocalPosition() + (m_Direction * deltaTime));
		m_Direction = glm::vec3{0,0,0}; //reset after movement is done!
		m_ShouldMove = false;
	}
}

void dae::MovementComponent::Move(Direction direction)
{
	switch (direction)
	{
	case Direction::Left:
		m_Direction.x -= m_MovementSpeed;
		break;
	case Direction::Right:
		m_Direction.x += m_MovementSpeed;
		break;
	case Direction::Up:
		m_Direction.y -= m_MovementSpeed;
		break;
	case Direction::Down:
		m_Direction.y += m_MovementSpeed;
		break;
	}

	m_ShouldMove = true;
}