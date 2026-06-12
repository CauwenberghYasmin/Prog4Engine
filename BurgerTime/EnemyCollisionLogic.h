//
// Created by yasmi on 6/12/2026.
//

#ifndef MINIGIN_ENEMYCOLLISIONLOGIC_H
#define MINIGIN_ENEMYCOLLISIONLOGIC_H
#include "Component.h"
#include "CollisionComponent.h"


class EnemyCollisionLogic final : public dae::Component
{
public:
    explicit EnemyCollisionLogic(dae::GameObject* owner, int id=0);
    ~EnemyCollisionLogic() override = default; //check if default or override even though smartpointers and polymorphism

    void OnEnterEnemy(CollisionComponent* other);
    void OnExitEnemy(CollisionComponent* other);

    void Render() override;
    void Update() override;


    bool m_IsHitBySpray{false};
    bool m_IsOnBurger{false};
    bool m_IsHitByBurger{false};

    [[nodiscard]] bool IsTouchingTile () const { return m_TileTouchCount > 0; }
    [[nodiscard]] bool IsTouchingLadder() const { return m_LadderTouchCount > 0; }

private:

    int m_TileTouchCount{ 0 };
    int m_LadderTouchCount{ 0 };
    //doesnt check if hit player -> players job!
};


#endif //MINIGIN_ENEMYCOLLISIONLOGIC_H


