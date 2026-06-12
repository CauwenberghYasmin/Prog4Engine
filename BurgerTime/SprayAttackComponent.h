//
// Created by yasmi on 6/12/2026.
//

#ifndef MINIGIN_SPRAYATTACK_H
#define MINIGIN_SPRAYATTACK_H
#include "Component.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "PlayerStateComponent.h"


class SprayAttackComponent final : public dae::Component
{ //so the object should also have a render component
public:
    SprayAttackComponent(dae::GameObject* pOwner, dae::GameObject* pSprayChild, int amountSprays = 5, int id = 0);


    void Spray(PlayerStateComponent::Direction facingDir);
    void Update() override;
    void Render() override;

private:

    dae::GameObject* m_pSprayChild;
    int m_AmountSprays;
    bool m_IsActive{ false };
    float m_Timer{ 0.0f };
    const float m_SprayDuration{ 0.2f }; // Stays active for 1.5 seconds
    void DeactivateSpray();


    dae::RenderComponent* m_RendComponent;
    CollisionComponent* m_CollComponent;

    //Direction
    //SetDirection -> get direction from player state (was set by the command)

    //spray attack is a component given to a child object of the player
    //the position is determined by the last orientation the player had (left/right/up/down) and is a distance in front of that
    //the enemy should handle the collision logic: (if object hit has tag spray etc)

    //the comp should hava a on/off thingy (if sprayed visible for a couple seconds + can be collided with)
    //also has an amount, you can only spray a set amount of times

    //make own collisionComp
    //->give tag spray

};


#endif //MINIGIN_SPRAYATTACK_H
