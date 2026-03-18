#pragma once
#include "Component.h"

namespace dae
{
    class GameObject;
    class HealthComponent final : public Component
    {
    public:
        HealthComponent(GameObject* pGameObject, int id, int startingHealth);
        ~HealthComponent() = default;
       

        int GetCurrentHealth();
        bool isDead();
        //void DoDamage(int amountDamage);
        void ChangeHealth(int amountHealthChange); //add pos for healing, add negative for damage
        void ResetHealth();

        void Render() {}; //adding these because both are pure functions
        void Update() {};

        HealthComponent(const HealthComponent&) = delete;
        HealthComponent& operator=(const HealthComponent&) = delete;

    private:
        const int m_StartHealth{};
        int m_CurrentHealth{};
    };

}