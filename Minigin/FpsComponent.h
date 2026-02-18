#pragma once
#include <string>
#include "FPSComponent.h"
#include"Component.h"
#include "TextObject.h"
#include<memory>
#include <SDL3/SDL.h>

namespace dae
{
    class FPSComponent: public Component //-> no inherit, cause willl be part of textObject (is component)
    {
    public:
        FPSComponent(dae::TextObject* pText, float id) : 
            m_pTextComp(pText), Component(id) {}

        virtual void Update() override;
        virtual void Render() override;

        FPSComponent(const FPSComponent&) = delete;
        ~FPSComponent() = default;
        FPSComponent& operator=(const FPSComponent&) = delete;
     
    private:
        dae::TextObject* m_pTextComp{};
        float fps{};
        
    };

}
