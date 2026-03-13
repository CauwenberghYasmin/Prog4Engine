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
//
//void dae::MovementComponent::Update()
//{
//	int i = 1;
//	++i;
//}
//
//void dae::MovementComponent::Move(Direction direction)
//{
//	int i = 1;
//	++i;
//}