//
// Created by yasmi on 6/12/2026.
//

#include "SprayAttackComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"

SprayAttackComponent::SprayAttackComponent(dae::GameObject* pOwner, dae::GameObject* pSprayChild, int amountSprays, int id)
        : Component(pOwner, id), m_pSprayChild(pSprayChild), m_AmountSprays(amountSprays)
{
    m_RendComponent = m_pSprayChild->GetComponent<dae::RenderComponent>();
    m_CollComponent = m_pSprayChild->GetComponent<CollisionComponent>();

    DeactivateSpray();
}


void SprayAttackComponent::Spray(PlayerStateComponent::Direction facingDir) {
    if (m_AmountSprays <= 0) return; // Can't spray if already spraying or empty

    --m_AmountSprays;
    m_IsActive = true;
    m_Timer = m_SprayDuration;

    dae::ServiceLocator::get_sound_system().PlaySound(3, 50); //pass by observer!!

    float offset = 27.f;
    switch (facingDir)
        {
        case PlayerStateComponent::Direction::Left:
            m_pSprayChild->SetLocalPosition((glm::vec3(-offset, 0, 0)));
            break;
        case PlayerStateComponent::Direction::Right:
            m_pSprayChild->SetLocalPosition(glm::vec3(offset, 0, 0));
            break;
        case PlayerStateComponent::Direction::Up:
            m_pSprayChild->SetLocalPosition(glm::vec3(0, -offset, 0));
            break;
        case PlayerStateComponent::Direction::Down:
            m_pSprayChild->SetLocalPosition(glm::vec3(0, offset, 0));
            break;
    }

    m_RendComponent->m_IsRendering = true;
    m_CollComponent->m_IsCollisionOn = true;
}

void SprayAttackComponent::Render() { }

void SprayAttackComponent::Update() {
    if (!m_IsActive) return;

    m_Timer -= dae::GameTime::GetInstance().GetDeltaTime();

    if (m_Timer <= 0.0f) {
        DeactivateSpray();
    }
}

void SprayAttackComponent::DeactivateSpray() {
    m_IsActive = false;

    m_RendComponent->m_IsRendering = false;
    m_CollComponent->m_IsCollisionOn = false;
}

//IN RENDER: m_IsRendering -> SET TO FALSE!!!