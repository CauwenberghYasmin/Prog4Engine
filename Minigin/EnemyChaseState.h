#pragma once
#include <SDL3/SDL_stdinc.h>

#include "EnemyState.h"


class EnemyChaseState final : public EnemyState
{
public:
    void OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players) override;
    void OnExit(dae::GameObject* pOwner) override;
    std::unique_ptr<EnemyState> Update(dae::GameObject* pOwner) override;

private:
    float m_WalkSpeed{ 90 };
    glm::vec3 m_MoveDirection{ 1.0f, 0.0f, 0.0f };

    glm::vec3 m_LastPosition{};
    float m_StuckTimer{0.f};
    dae::GameObject* m_pTargetPlayer{};
};