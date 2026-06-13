//
// Created by yasmi on 6/13/2026.
//

#include "PickUpSpawner.h"

#include <SDL3/SDL_stdinc.h>

#include "CollisionComponent.h"
#include "ObserverManager.h"
#include "PickUpComponent.h"
#include "RenderComponent.h"

PickUpSpawner::PickUpSpawner(dae::GameObject* owner, std::vector<glm::vec2>positions, int amountItems, dae::Scene* scene, int id):
                Component(owner, id), m_AmountItems(amountItems)
{
    for (const auto& pos: positions) {
        auto item = std::make_unique<dae::GameObject>();
        item->Tag = "PickUp";

        std::string texturePath;
        int random = SDL_rand(2);
        if (random == 0) {
            texturePath = spritePathfries;
        }
        else {
            texturePath = spritePathHotIceCream;
        }


        auto renderComp = std::make_unique<dae::RenderComponent>(item.get());
        renderComp->SetTexture(texturePath);
        glm::vec2 startPos = pos;
        renderComp->SetPosition(startPos.x, startPos.y);
        item->AddComponent(std::move(renderComp));
        auto pickupComp = std::make_unique<PickUpComponent>(item.get(), 700);
        pickupComp->SetOnCollectCallback([this](dae::GameObject* collectedItem) {
            this->PickedUp(collectedItem);
        });
        item->AddComponent(std::move(pickupComp));

        auto collComp = std::make_unique<CollisionComponent>(item.get(), false);
        item->AddComponent(std::move(collComp));

       scene->Add(std::move(item));
    }
}

void PickUpSpawner::PickedUp(dae::GameObject* object) {
    auto coll = object->GetComponent<CollisionComponent>();
    coll->m_IsCollisionOn = false;

    auto ren = object->GetComponent<dae::RenderComponent>();
    ren->m_IsRendering = false;

    ++m_CollectedItems;


    if (m_CollectedItems == m_AmountItems) {
        dae::ObserverManager::GetInstance().NotifyObserver(GetOwner(), dae::Event::LevelComplete);
    }
}


void PickUpSpawner::Update() {}