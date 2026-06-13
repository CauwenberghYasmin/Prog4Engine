//
// Created by yasmi on 6/12/2026.
//
#include "EnemyCrushedState.h"
#include "EnemyBehaviourComponent.h"
#include "GameObject.h"
#include "ObserverManager.h"

void EnemyCrushedState::OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players)
{
    if (players[0] == nullptr) return; //warning unreferenced paramterer-> might as well use for safety check

    m_HasReachedGrid = false;
    auto behaviour = pOwner->GetComponent<EnemyBehaviourComponent>();
    if (behaviour) {
        dae::ObserverManager::GetInstance().NotifyObserver(pOwner, dae::Event::EnemyDied);
        //also notify score system etc
    }
}


std::unique_ptr<EnemyState> EnemyCrushedState::Update(dae::GameObject* pOwner)
{

    if (pOwner == nullptr) return nullptr;

    return nullptr;//wait till respawn in enemySpawner
}

void EnemyCrushedState::OnExit(dae::GameObject* pOwner)
{
    if (pOwner == nullptr) return;
}
