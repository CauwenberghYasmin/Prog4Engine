#pragma once
#include "FpsComponent.h"
#include "GameTime.h"
#include "TextObject.h"
#include "Component.h"
#include "GameObject.h"
#include <string>
#include <format>


void dae::FPSComponent::Update() {
    float dt = dae::GameTime::GetInstance().GetDeltaTime();
    fps = 1.0f / dt;

    const std::string fpsString{ std::format("{:.2f}", fps) };

    //if (fps != pastFps)
    if (std::abs(fps - pastFps) > 0.5) //only renew if difference is big enough
    {
        auto textComp = GetOwner()->Get<TextComponent>();
        textComp->SetText(fpsString);
        pastFps = fps;
    }
}

void dae::FPSComponent::Render() {
//////
}