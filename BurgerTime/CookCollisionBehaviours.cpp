//
// Created by yasmi on 6/11/2026.
//

#include "CookCollisionBehaviours.h"



CookCollisionBehaviours:: CookCollisionBehaviours(dae::GameObject* owner, int id) :
    Component(owner, id)

{
}

void CookCollisionBehaviours::Update() {

}

void CookCollisionBehaviours::Render() {

}


void CookCollisionBehaviours::OnEnterCook(CollisionComponent* other) {

    std::string tag {other->GetOwnerTag()};


    if (tag == "Tile")
    {
        m_IsTouchingTile = true;
    }

    if (tag == "Ladder")
    {
        m_IsTouchingLadder = true;
    }

    if (tag == "Enemy")
    {
        //call damage, like in the command class
        //update all the observers!!!
        //make a list of observers to make!
    }

    if (tag == "Burger")
    {
        //dont check this here
        //check this in burgerclass!
        //check if it was the last bun!
        //also check if enemy was on it? -> extra points
    }



    if (tag == "PickUp")
    {
        //do bonus points
        //update observer for the text
        //remove image after!
        // -> object pooling?
    }

}
void CookCollisionBehaviours::OnExitCook(CollisionComponent* other) {

    std::string tag {other->GetOwnerTag()};

    if (tag == "Tile")
    {
        m_IsTouchingTile = false;
    }

    if (tag == "Ladder")
    {
        m_IsTouchingLadder = false;
    }
}