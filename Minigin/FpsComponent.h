#pragma once
#include <string>
#include "FPSComponent.h"
#include"Component.h"
#include "TextObject.h"
#include<memory>
#include <SDL3/SDL.h>

namespace dae
{
    class FPSComponent//: public Component -> no inherit, cause willl be part of textObject (is component)
    {
    public:
        explicit FPSComponent(std::unique_ptr<TextObject> textComponent);
         void Update();
        // void Render() override;

        FPSComponent(const FPSComponent&) = delete;
        ~FPSComponent() = default;
        FPSComponent& operator=(const FPSComponent&) = delete;
     
    private:
        std::unique_ptr<TextObject> textComp;
        float fps{};
        
    };

}
