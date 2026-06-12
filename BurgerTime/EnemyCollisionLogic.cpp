//
// Created by yasmi on 6/12/2026.
//

#include "EnemyCollisionLogic.h"
#include "GameTime.h"

EnemyCollisionLogic:: EnemyCollisionLogic(dae::GameObject* owner, int id) :
    Component(owner, id)
{

    auto* coll = GetOwner()->GetComponent<CollisionComponent>();
    if (coll == nullptr) assert("create collision component before adding collisionBehaviour!");

    coll->SetFunction([this](CollisionComponent* other) {
        this->OnEnterEnemy(other);
    }, CollisionComponent::CollisionType::OnEnter);

    coll->SetFunction([this](CollisionComponent* other) {
        this->OnExitEnemy(other);
    }, CollisionComponent::CollisionType::OnExit);


}

void EnemyCollisionLogic::OnEnterEnemy(CollisionComponent* other) {

    const std::string tag = other->GetOwnerTag();

    if (tag == "Spray") {
        m_IsHitBySpray = true;
        //do timer in the state section!
    }

    if (tag == "Burger") {
        //if on top
        //set dying + notify score

        //if bottom
        //check if burger is falling!
    }

    if (tag == "Tile")
    {
        ++m_TileTouchCount;
    }

    if (tag == "Ladder")
    {
        ++m_LadderTouchCount;
    }


}
void EnemyCollisionLogic::OnExitEnemy(CollisionComponent* other) {

    const std::string tag {other->GetOwnerTag()};

    if (tag == "Burger") {
        //not on burger anymore
    }

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



void EnemyCollisionLogic::Render() {}

void EnemyCollisionLogic::Update() {}