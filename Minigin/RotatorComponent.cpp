#include "RotatorComponent.h"
#include "GameObject.h"
#include"Component.h"
#include "GameTime.h"
#include <iostream>

dae::RotatorComponent::RotatorComponent(GameObject* pGameObject, int id, const glm::vec3& pivot, bool goesClockWise, float speed)
    : Component(pGameObject, id)
    , m_Pivot{ pivot }
    , m_GoesClockWise{ goesClockWise }
    , m_distance{ static_cast<float>(glm::length(GetOwner()->GetLocalPosition() - m_Pivot)) } 
    , m_Speed{speed}
{
}

void dae::RotatorComponent::Update() 
{
    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

    float currentSpeed = m_GoesClockWise ? -m_Speed : m_Speed;
    m_angle += currentSpeed * deltaTime;


    float x{ cos(m_angle) * m_distance};
    float y{ sin(m_angle) * m_distance};
    glm::vec3 newPos{ m_Pivot + glm::vec3{ x, y, 0 } };
    GetOwner()->SetLocalPosition(newPos);
}


void dae::RotatorComponent::Render(){}