#pragma once
#include "FpsComponent.h"
#include "GameTime.h"
#include "TextObject.h"
#include <format>
#include "Component.h"

void dae::FPSComponent::Update() {
    float dt = dae::GameTime::GetInstance().GetDeltaTime();
    fps = 1.0f / dt;
    if (m_pTextComp) {
        m_pTextComp->SetText(std::format("FPS: {:.1f}", fps));
    }
}

void dae::FPSComponent::Render(){}