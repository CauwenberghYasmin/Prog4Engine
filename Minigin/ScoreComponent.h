#pragma once

#pragma once
#include "Component.h"

namespace dae
{
    class GameObject;
    class ScoreComponent final : public Component
    {
    public:
        ScoreComponent(GameObject* pGameObject, int id, int startingScore = 0);
        ~ScoreComponent() = default;


        int GetCurrentScore();
        void AddScorePoints(int addScoreAmount);
        void LoseScorePoints(int amountToLose);
        

        ScoreComponent(const ScoreComponent&) = delete;
        ScoreComponent& operator=(const ScoreComponent&) = delete;

        void Render() {}; //adding these because both are pure functions
        void Update() {};

    private:
        int m_CurrentScore{};
    };

}