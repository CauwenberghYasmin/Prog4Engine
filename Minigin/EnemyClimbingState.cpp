//
// Created by yasmi on 6/12/2026.
//

#include "EnemyClimbingState.h"
#include "EnemyChaseState.h"
#include "EnemyStunState.h"
#include "EnemyCrushedState.h"
#include "EnemyCollisionLogic.h"
#include "GameObject.h"
#include "GameTime.h"

void EnemyClimbingState::OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players)
{
    glm::vec3 myPos = pOwner->GetLocalPosition();
    dae::GameObject* pTargetPlayer = nullptr;
    float closestDistance = FLT_MAX;

    for (auto* player : players)
    {
        float distance = glm::distance(myPos, player->GetLocalPosition());
        if (distance < closestDistance)
        {
            closestDistance = distance;
            pTargetPlayer = player;
        }
        m_Players.emplace_back(pTargetPlayer);
    }

    if (pTargetPlayer)
    {
        float playerY = pTargetPlayer->GetLocalPosition().y;

        if (playerY < myPos.y)
        {
            m_ClimbDirection = -1.0f;
        }
        else
        {
            m_ClimbDirection = 1.0f;
        }
    }


}

void EnemyClimbingState::OnExit(dae::GameObject *pOwner) {
    if (pOwner) return;
}

std::unique_ptr<EnemyState> EnemyClimbingState::Update(dae::GameObject* pOwner)
{
    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
    auto collision = pOwner->GetComponent<EnemyCollisionLogic>();
    glm::vec3 pos = pOwner->GetLocalPosition();

    if (collision->m_IsHitBySpray) return std::make_unique<EnemyStunState>();
    if (collision->m_IsHitByBurger) return std::make_unique<EnemyCrushedState>();

    if (collision->IsTouchingTile())
    {
        float tileAlignmentMargin = 4.0f;

        for (auto* player : m_Players)
        {
            float yDiff = std::abs(player->GetLocalPosition().y - pos.y);
            if (yDiff <= tileAlignmentMargin)
            {
                return std::make_unique<EnemyChaseState>();
            }
        }
    }

    if (!collision->IsTouchingLadder() && collision->IsTouchingTile())
    {
        return std::make_unique<EnemyChaseState>();
    }

    //might need some behaviour when stuck on bottoms ladder and not touching a tile...


    pos.y += m_ClimbDirection * (m_ClimbSpeed * deltaTime);
    pOwner->SetLocalPosition(pos);

    return nullptr;
}
