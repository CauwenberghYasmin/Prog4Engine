//
// Created by yasmi on 6/11/2026.
//

#ifndef MINIGIN_COOKCOLLISIONBEHAVIOURS_H
#define MINIGIN_COOKCOLLISIONBEHAVIOURS_H
#include "Component.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"


class CookCollisionBehaviours final : public dae::Component
{
public:
    explicit CookCollisionBehaviours(dae::GameObject* owner, int id=0);
    ~CookCollisionBehaviours() override = default; //check if default or override even though smartpointers and polymorphism

    void OnEnterCook(CollisionComponent* other);
    void OnExitCook(CollisionComponent* other);

    void Render() override;
    void Update() override;

    //public -> access by command class (no trivial getters and setters!)
    [[nodiscard]] bool IsTouchingTile () const { return m_TileTouchCount > 0; }
    [[nodiscard]] bool IsTouchingLadder() const { return m_LadderTouchCount > 0; }

    glm::vec3 m_OldPos;
private:
    int m_TileTouchCount{ 0 };
    int m_LadderTouchCount{ 0 };
    bool m_OnAwake{true};

    dae::HealthComponent* m_ObjectsHealthComponent;
};


#endif //MINIGIN_COOKCOLLISIONBEHAVIOURS_H
