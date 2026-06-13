
#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "EnemyState.h"


    class GameObject;
    class EnemyBehaviourComponent final : public dae::Component//kinda like a state manager
    {
    public:
        enum class EnemyTypes {
            HotDog,
            Pickle,
            Egg
        };


        EnemyBehaviourComponent(dae::GameObject* pGameObject, EnemyTypes enemyType, std::vector<dae::GameObject*> players,  int id=0); //add id, rendercomponent? (needs to draw sprite)

        virtual void Update() override;
        virtual void Render() override;

        void SetStartState( std::unique_ptr<EnemyState> CurrentState);


        bool m_IsActive{false};


        EnemyTypes m_EnemyType;
        std::vector<dae::GameObject*> m_Players;

        // ~EnemyBehaviourComponent() = default;
        // EnemyBehaviourComponent(const EnemyBehaviourComponent& other) = delete;
        // EnemyBehaviourComponent(EnemyBehaviourComponent&& other) = delete;
        // EnemyBehaviourComponent& operator=(const EnemyBehaviourComponent& other) = delete;
        // EnemyBehaviourComponent& operator=(EnemyBehaviourComponent&& other) = delete;

    private:
        std::unique_ptr<EnemyState> m_pCurrentState;

    };
//}