
#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include "HotDogState.h"

//namespace dae //TRIGGERED BY COLLISIONS!!!!
//{
//    class GameObject;
//    class HotDogBehaviourComponent final : public Component
//    {
//    public:
//        HotDogBehaviourComponent(GameObject* pGameObject); //add id, rendercomponent? (needs to draw sprite)
//
//        virtual void Update() override;
//        virtual void Render() override;
//
//
//        
//
//        ~HotDogBehaviourComponent() = default;
//        HotDogBehaviourComponent(const HotDogBehaviourComponent& other) = delete;
//        HotDogBehaviourComponent(HotDogBehaviourComponent&& other) = delete;
//        HotDogBehaviourComponent& operator=(const HotDogBehaviourComponent& other) = delete;
//        HotDogBehaviourComponent& operator=(HotDogBehaviourComponent&& other) = delete;
//
//    private:
//        HotDogState* currentState;
//
//    };
//}