#pragma once
#include "Component.h"

namespace dae
{
    class GameObject;
    class HealthComponent final : public Component
    {
    public:
        HealthComponent(GameObject* pGameObject, int startingHealth, int id = 0 );
        ~HealthComponent() override = default;
       

        [[nodiscard]] int GetCurrentHealth() const;
        [[nodiscard]] bool isDead() const;
        //void DoDamage(int amountDamage);
        void ChangeHealth(int amountHealthChange); //add pos for healing, add negative for damage
        void ResetHealth();

        void Render() override{}; //adding these because both are pure functions
        void Update() override{};

        HealthComponent(const HealthComponent&) = delete;
        HealthComponent& operator=(const HealthComponent&) = delete;

    private:
        const int m_StartHealth{};
        int m_CurrentHealth{};
    };

}