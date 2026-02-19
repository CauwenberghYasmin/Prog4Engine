#pragma once
#include "Singleton.h"

//use: float dt = dae::GameTime::GetInstance().GetDeltaTime();

namespace dae {
    class GameTime final : public Singleton<GameTime>
    {
    public:
        float GetDeltaTime() const { return m_DeltaTime; }
        void SetDeltaTime(float dt) { m_DeltaTime = dt; }

    private:
        // Friend allows the base Singleton to access the private constructor
        //-> prevents making more than one instance
        friend class Singleton<GameTime>;
        GameTime() = default;

        float m_DeltaTime = 0.0f;
    };
} //adkbgf;kdrbg

//https://refactoring.guru/design-patterns/singleton

