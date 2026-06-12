//
// Created by yasmi on 6/12/2026.
//
#include "EnemyStunState.h"

#include "EnemyBehaviourComponent.h"
#include "EnemyChaseState.h"
#include "EnemyCrushedState.h"
#include "EnemyCollisionLogic.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "GameTime.h"


void EnemyStunState::OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players)
{

    if (players[0] == nullptr) return; //warning unreferenced paramterer-> might as well use for safety check

   auto type = pOwner->GetComponent<EnemyBehaviourComponent>()->m_EnemyType;
   auto render = pOwner->GetComponent<dae::RenderComponent>();

    switch (type) {
        case EnemyBehaviourComponent::EnemyTypes::HotDog:
            render->SetTexture(spritePathHotDogStunned);
            break;
        case EnemyBehaviourComponent::EnemyTypes::Egg:
            render->SetTexture(spritePathEggStunned);
            break;
        case EnemyBehaviourComponent::EnemyTypes::Pickle:
            render->SetTexture(spritePathPickleStunned);
            break;
    }

}

void EnemyStunState::OnExit(dae::GameObject* pOwner)
{
    auto type = pOwner->GetComponent<EnemyBehaviourComponent>()->m_EnemyType;
    auto render = pOwner->GetComponent<dae::RenderComponent>();

    switch (type) {
        case EnemyBehaviourComponent::EnemyTypes::HotDog:
            render->SetTexture(spritePathHotDog);
            break;
        case EnemyBehaviourComponent::EnemyTypes::Egg:
            render->SetTexture(spritePathEgg);
            break;
        case EnemyBehaviourComponent::EnemyTypes::Pickle:
            render->SetTexture(spritePathPickle);
            break;
    }
}

std::unique_ptr<EnemyState> EnemyStunState::Update(dae::GameObject* pOwner)
{
    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
    auto collision = pOwner->GetComponent<EnemyCollisionLogic>();

    //burgerfall -> forced death!
    if (collision->m_IsHitByBurger) {
        return std::make_unique<EnemyCrushedState>();
    }


    m_StunTimer -= deltaTime;
    if (m_StunTimer <= 0.0f) {
        return std::make_unique<EnemyChaseState>();
    }

    return nullptr;
}