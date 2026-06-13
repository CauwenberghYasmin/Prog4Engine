//
// Created by yasmi on 6/11/2026.
//

#include "CookCollisionBehaviours.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "ObserverManager.h"
#include "PickUpComponent.h"


CookCollisionBehaviours:: CookCollisionBehaviours(dae::GameObject* owner, int id) :
    Component(owner, id)
{
    m_OldPos = owner->GetLocalPosition();
    m_ObjectsHealthComponent = GetOwner()->GetComponent<dae::HealthComponent>();
}

void CookCollisionBehaviours::Update() {

    if (m_OnAwake) //works like onawake, unity (make init function?)
    {

        auto* coll = GetOwner()->GetComponent<CollisionComponent>();
        if (coll == nullptr) assert("create collision component before adding collisionBehaviour!");

        coll->SetFunction([this](CollisionComponent* other) {
            this->OnEnterCook(other);
        }, CollisionComponent::CollisionType::OnEnter);

        coll->SetFunction([this](CollisionComponent* other) {
            this->OnExitCook(other);
        }, CollisionComponent::CollisionType::OnExit);

        m_OnAwake = false;
    }
}

void CookCollisionBehaviours::Render() {

}


void CookCollisionBehaviours::OnEnterCook(CollisionComponent* other) {

    std::string tag {other->GetOwnerTag()};

    if (tag == "Tile")
    {
        ++m_TileTouchCount;
    }

    if (tag == "Ladder")
    {
        ++m_LadderTouchCount;
    }

    if (tag == "Enemy")
    {
        if (m_ObjectsHealthComponent == nullptr) {
            m_ObjectsHealthComponent = GetOwner()->GetComponent<dae::HealthComponent>();
        }
        m_ObjectsHealthComponent->ChangeHealth(-1);
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



    if (tag == "PickUp") //-> extra!!! wasn't in the requirements!
    {
        dae::GameObject* itemObject = other->GetOwner();
        if (auto pickupComp = itemObject->GetComponent<PickUpComponent>())
        {
            pickupComp->Collect(GetOwner());
        }
        //dae::ObserverManager::GetInstance().NotifyObserver(GetOwner(), dae::Event::ItemPickedUp); //yes this is how to send stuff!

    }

}
void CookCollisionBehaviours::OnExitCook(CollisionComponent* other) {

    std::string tag {other->GetOwnerTag()};

    if (tag == "Tile")
    {
       --m_TileTouchCount;
        if (m_TileTouchCount < 0) m_TileTouchCount = 0;
    }

    if (tag == "Ladder")
    {
       --m_LadderTouchCount;
        if (m_LadderTouchCount < 0) m_LadderTouchCount = 0;
    }
}