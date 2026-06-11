//
// Created by yasmi on 6/11/2026.
//

#ifndef MINIGIN_COOKCOLLISIONBEHAVIOURS_H
#define MINIGIN_COOKCOLLISIONBEHAVIOURS_H
#include "Component.h"
#include "GameObject.h"
#include "CollisionComponent.h"


class CookCollisionBehaviours final : public dae::Component
{
public:
    explicit CookCollisionBehaviours(dae::GameObject* owner, int id=0);
    ~CookCollisionBehaviours() = default; //check if default or override even though smartpointers and polymorphism

    void OnEnterCook(CollisionComponent* other);
    void OnExitCook(CollisionComponent* other);

    void Render() override;
    void Update() override;

    //public -> access by command class (no trivial getters and setters!)
    bool m_IsTouchingTile{false};
    bool m_IsTouchingLadder{false};
private:
};


#endif //MINIGIN_COOKCOLLISIONBEHAVIOURS_H
