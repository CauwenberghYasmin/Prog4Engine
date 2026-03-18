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
        void DoDamage(int amountDamage);
        void HealCharacter(int amountHealing);
        void ResetHealth();

        HealthComponent(const HealthComponent&) = delete;
        HealthComponent& operator=(const HealthComponent&) = delete;

    private:
        const int m_StartHealth{};
        int m_CurrentHealth{};
    };

}