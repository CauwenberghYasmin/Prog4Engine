//#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
    enum class Direction {
        Up,
        Down,
        Left,
        Right
    };

    class TransformComponent;
    class GameObject;
    class MovementComponent final : public Component
    {
    public:
        MovementComponent(GameObject* pGameObject, int id, float movementSpeed = 50.f);
            //Component(pGameObject, id), m_MovementSpeed(movementSpeed)
      

        virtual void Update() override;
        void Move(Direction direction);

        
        //revise done correctly
        MovementComponent(const MovementComponent&) = delete;
        ~MovementComponent() = default;
        MovementComponent& operator=(const MovementComponent&) = delete;

    private:
        float m_MovementSpeed{};
        bool m_ShouldMove{ false };
        glm::vec3 m_Direction{};
      
    };

}