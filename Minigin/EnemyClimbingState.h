#pragma once
#include "EnemyState.h"


//LADDER
class EnemyClimbingState final : public EnemyState
{
public:
    void OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players) override;
    void OnExit(dae::GameObject* pOwner) override;
    std::unique_ptr<EnemyState> Update(dae::GameObject* pOwner) override;

private:
    float m_ClimbSpeed{ 40.0f };
    float m_ClimbDirection{ 1.0f }; // 1 = down, -1 = up (axis upside down!)
    std::vector<dae::GameObject*> m_Players;
};