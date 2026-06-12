//
// Created by yasmi on 6/12/2026.
//

#include "EnemySpawner.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "EnemyCollisionLogic.h"
#include "EnemyBehaviourComponent.h"
#include "EnemyChaseState.h"
#include "Observer.h"
#include "GameTime.h"
#include <random>
#include <SDL3/SDL_stdinc.h>

#include "ObserverManager.h"


//temp -> see if can replace later!
class SpawnerObserver final : public dae::IObserver {
public:
    SpawnerObserver(EnemySpawner* pSpawner) : m_pSpawner(pSpawner) {}

    void Notify(dae::Event event, dae::GameObject* actor) override { //to make state access the kill function (avoid enemybehaviourcomp)
        if (event == dae::Event::EnemyDied) {
            m_pSpawner->KillEnemy(actor);
        }
    }
private:
    EnemySpawner* m_pSpawner;
};



EnemySpawner::EnemySpawner(dae::GameObject* owner, std::vector<dae::GameObject*> players, std::vector<glm::vec2> positions, int amountEnemies, dae::Scene* scene, int id) :
    Component(owner, id), m_Players(std::move(players)), m_SpawnPositions(std::move(positions)), m_MaxAmountEnemies(amountEnemies), m_Scene(scene)
{
    for (int i = 0; i < m_MaxAmountEnemies; ++i)
    {
        auto enemyObj = std::make_unique<dae::GameObject>();
        enemyObj->Tag = "Enemy";


        std::string texturePath;
        int randomType = SDL_rand(3);
        EnemyBehaviourComponent::EnemyTypes type;
        if (randomType == 0)
        {
            texturePath = spritePathHotDog;
            type =  EnemyBehaviourComponent::EnemyTypes::HotDog;
        }
        else if (randomType == 1) {
            texturePath = spritePathEgg;
            type =  EnemyBehaviourComponent::EnemyTypes::Egg;
        }
        else
        {
            texturePath = spritePathPickle;
            type =  EnemyBehaviourComponent::EnemyTypes::Pickle;
        }


        auto renderComp = std::make_unique<dae::RenderComponent>(enemyObj.get());
        renderComp->SetTexture(texturePath);
        glm::vec2 startPos = m_SpawnPositions[i];
        renderComp->SetPosition(startPos.x, startPos.y);
        const glm::vec2 size = renderComp->GetTextureSize(); //bottom coll
        enemyObj->AddComponent(std::move(renderComp));

        auto collComp = std::make_unique<CollisionComponent>(enemyObj.get(), false);
        collComp->SetCollisionBox(size.x, size.y/3, CollisionComponent::Alignment::Bottom);
        enemyObj->AddComponent(std::move(collComp));

        enemyObj->AddComponent(std::make_unique<EnemyCollisionLogic>(enemyObj.get())); //check if can find collComp!!!

        //behaviourr
        auto behaviourComp = std::make_unique<EnemyBehaviourComponent>(enemyObj.get(), type, m_Players);
        behaviourComp->SetStartState(std::move(std::make_unique<EnemyChaseState>()));
        enemyObj->AddComponent(std::move(behaviourComp));

        dae::GameObject* safeEnemyPtr = enemyObj.get();
        m_Enemies.emplace_back(safeEnemyPtr); //fake error?

        dae::ObserverManager::GetInstance().AddObserver(
        enemyObj.get(),
        std::make_unique<SpawnerObserver>(this) // 'this' is the EnemySpawner
);

        m_Scene->Add(std::move(enemyObj));
    }
}

void EnemySpawner::Update()
{
    float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

    //backwards loop (SAFETY AS IN REMOVING GAMEOBJECTS PPT1)
    for (int i = static_cast<int>(m_RespawnQueue.size()) - 1; i >= 0; --i)
    {
        m_RespawnQueue[i].timeRemaining -= deltaTime;

        if (m_RespawnQueue[i].timeRemaining <= 0.0f)
        {
            RespawnEnemy(m_RespawnQueue[i].pEnemy);
            m_RespawnQueue.erase(m_RespawnQueue.begin() + i);
        }
    }
}

void EnemySpawner::KillEnemy(dae::GameObject* pEnemy)
{
    pEnemy->GetComponent<dae::RenderComponent>()->m_IsRendering = false;
    pEnemy->GetComponent<CollisionComponent>()->m_IsCollisionOn = false;

    m_RespawnQueue.push_back({ pEnemy, 3.0f });
}

void EnemySpawner::RespawnEnemy(dae::GameObject* pEnemy)
{
    const int rand {(SDL_rand(static_cast<int>(m_SpawnPositions.size())))};
    glm::vec2 spawnPos = m_SpawnPositions[rand];
    pEnemy->SetLocalPosition(glm::vec3(spawnPos.x, spawnPos.y, 0.0f));

    //resetss
    auto collisionLogic = pEnemy->GetComponent<EnemyCollisionLogic>();
    collisionLogic->m_IsHitBySpray = false;
    collisionLogic->m_IsHitByBurger = false;


    auto behaviour = pEnemy->GetComponent<EnemyBehaviourComponent>();
    behaviour->SetStartState(std::make_unique<EnemyChaseState>());

    pEnemy->GetComponent<dae::RenderComponent>()->m_IsRendering = true;
    pEnemy->GetComponent<CollisionComponent>()->m_IsCollisionOn = true;
}

void EnemySpawner::Render(){}
