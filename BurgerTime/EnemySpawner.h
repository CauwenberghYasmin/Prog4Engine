//
// Created by yasmi on 6/12/2026.
//

#ifndef MINIGIN_ENEMYSPAWNER_H
#define MINIGIN_ENEMYSPAWNER_H
#include "GameObject.h"
#include "Scene.h"


//inline reduces overhead :0 (LOOK MORE INTO IT!!)
    inline static const std::string spritePathHotDog {"HotDog.png"};
    inline static const std::string spritePathHotDogStunned {"HotDogSprayed.png"};
    inline static const std::string spritePathEgg {"Egg.png"};
    inline static const std::string spritePathEggStunned {"EggSprayed.png"};
    inline static const std::string spritePathPickle{"Pickle.png"};
    inline static const std::string spritePathPickleStunned{ "PickleSprayed.png"};

class EnemySpawner final : public dae::Component {
public:
    EnemySpawner(dae::GameObject* owner, std::vector<dae::GameObject*>players, std::vector<glm::vec2>positions, int amountEnemies, dae::Scene* scene, int id =0);

    //sets positions and spritesheets (rand from 3)
    //give components (render component, collisioncomp, enemycollisionLogic)
    //reuses for object pooling!

    //respawns them once dead
    //takes notifications of one died, waits 3 seconds and then spawns a new one

    //instance created in each scene

    void Update() override;
    void Render() override; //enemies get rendered by the scene, DONT CALL HERE AGAIN!!!
    void KillEnemy(dae::GameObject* pEnemy);

private:
    std::vector<glm::vec2> m_SpawnPositions;
    int m_MaxAmountEnemies;
    dae::Scene* m_Scene;

    std::vector<dae::GameObject*> m_Enemies;
    std::vector<dae::GameObject*> m_Players; //for coop/single, finds closest player to focus on!


    struct RespawnTask {
        dae::GameObject* pEnemy;
        float timeRemaining;
    };
    std::vector<RespawnTask> m_RespawnQueue;

    void RespawnEnemy(dae::GameObject* pEnemy);
};


#endif //MINIGIN_ENEMYSPAWNER_H
