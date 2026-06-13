

#include "EnemyChaseState.h"
#include "EnemyClimbingState.h"
#include "EnemyCrushedState.h"
#include "EnemyCollisionLogic.h"
#include "EnemyStunState.h"
#include "GameObject.h"
#include "GameTime.h"

void EnemyChaseState::OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players)
{
    // safety check
    auto collision = pOwner->GetComponent<EnemyCollisionLogic>();
    collision->m_IsHitBySpray = false;

    m_pTargetPlayer = nullptr;
    float closestDistance = FLT_MAX;
    glm::vec3 myPos = pOwner->GetLocalPosition();

    for (auto* player : players) //2 or 1
    {
        float distance = glm::distance(myPos, player->GetLocalPosition()); //bless glm
        if (distance < closestDistance)
        {
            closestDistance = distance;
            m_pTargetPlayer = player;
        }
    }


    if (m_pTargetPlayer)
    {
        glm::vec3 targetPos = m_pTargetPlayer->GetLocalPosition();
        if (targetPos.x < myPos.x)
            m_MoveDirection = glm::vec3{ -1.f, 0.f, 0.f };//left
        else
        {
            m_MoveDirection = glm::vec3{ 1.f, 0.f, 0.f };
        }
    }
}

void EnemyChaseState::OnExit(dae::GameObject *pOwner)
{
    if (pOwner) return;
}

std::unique_ptr<EnemyState> EnemyChaseState::Update(dae::GameObject* pOwner)
{


    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();
    auto collision = pOwner->GetComponent<EnemyCollisionLogic>();
    glm::vec3 myPos = pOwner->GetLocalPosition();

    if (collision->IsTouchingLadder() || collision->IsTouchingTile())
    {
        m_HasReachedGrid = true; // Lock out spawn behavior forever!
    }

    //priorities
    if (collision->m_IsHitBySpray) return std::make_unique<EnemyStunState>();
    if (collision->m_IsHitByBurger) return std::make_unique<EnemyCrushedState>();
    //if (collision->m_IsOnBurger && burgerFalling (notify by observer?)) return std::make_unique<EnemyFallingState>();


    if (!m_HasReachedGrid) //while off level (usually spawn)
    {
        glm::vec3 targetPos = m_pTargetPlayer->GetLocalPosition();
        if (targetPos.x < myPos.x)
            m_MoveDirection.x = -1.f;//left
        else
        {
            m_MoveDirection.x = 1;
        }
        if (targetPos.y < myPos.y)
            m_MoveDirection.y = -1;
        else
        {
            m_MoveDirection.y = 1;
        }

        myPos += m_MoveDirection * (m_WalkSpeed * deltaTime);
        pOwner->SetLocalPosition(myPos);

        return nullptr;
    }

    m_MoveDirection.y = 0.f; //clear direction if on grid again
    //m_MoveDirection.x = 0.f; //clear direction if on grid again

    // check if stuck
    if (glm::distance(myPos, m_LastPosition) < 0.1f * deltaTime)
    {
        m_StuckTimer += deltaTime;
    }
    else
    {
        m_StuckTimer = 0.0f; // Moving fine, reset
    }
    m_LastPosition = myPos;


    if (collision->IsTouchingLadder())
    {
        glm::vec3 targetPos = m_pTargetPlayer->GetLocalPosition();
        float yDiff = targetPos.y - myPos.y;
        float yMargin = 4.0f;

        if (std::abs(yDiff) > yMargin) //if different level -> climb!
        {
            return std::make_unique<EnemyClimbingState>();
        }

        if (m_StuckTimer >= 0.5f)//if stuck end tile->force to climb (players props same height, but diff island)
        {
            return std::make_unique<EnemyClimbingState>();
        }
    }

    if (!collision->IsTouchingLadder() && !collision->IsTouchingTile()) //walking back
    {
        m_MoveDirection.x *= -1.f; // Reverse direction
        myPos.x += m_MoveDirection.x * (m_WalkSpeed * deltaTime);
        pOwner->SetLocalPosition(myPos);
        return nullptr;
    }

    myPos += m_MoveDirection * (m_WalkSpeed * deltaTime);
    pOwner->SetLocalPosition(myPos);

    return nullptr;
}
