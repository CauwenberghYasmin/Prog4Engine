#pragma once
#include <string>
#include"Component.h"
#include "TextComponent.h"
#include<memory>
#include <SDL3/SDL.h>


namespace dae
{
    class GameObject;
    class FPSComponent final: public Component
    {
    public:
        FPSComponent(GameObject* pGameObject, int id = 0) : //move constructor to cpp file!
            Component(pGameObject, id) {}

        virtual void Update() override;
        virtual void Render() override;

        float GetFps() { return fps; }

        FPSComponent(const FPSComponent&) = delete;
        ~FPSComponent() = default;
        FPSComponent& operator=(const FPSComponent&) = delete;
     
    private:
        float fps{};
        float pastFps{};

        float m_Timer{};
        float m_FrameCount{};
        
    };

}
