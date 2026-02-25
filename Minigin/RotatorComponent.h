#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class RotatorComponent final : public Component
    {
    public:
        RotatorComponent(GameObject* pGameObject, int id, const glm::vec3& pivot, bool goesClockWise);

        virtual void Update() override;
        virtual void Render() override;

        ~RotatorComponent() = default;
        RotatorComponent(const RotatorComponent& other) = delete;
        RotatorComponent(RotatorComponent&& other) = delete;
        RotatorComponent& operator=(const RotatorComponent& other) = delete;
        RotatorComponent& operator=(RotatorComponent&& other) = delete;


    private:
        glm::vec3 m_Pivot;    // local space
        bool m_GoesClockWise;
        float m_angle{ 0.f };
        float m_distance;

    };
}