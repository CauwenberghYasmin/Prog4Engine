#include "FpsComponent.h"
#include "GameTime.h"
#include "TextObject.h"
#include "Component.h"
#include "GameObject.h"
#include <string>
#include <format>


void dae::FPSComponent::Update() {
    float dt = dae::GameTime::GetInstance().GetDeltaTime();
   
    m_Timer += dt;
    m_FrameCount++;

    
    if (m_Timer >= 0.5f)
    {
        fps = static_cast<float>(m_FrameCount) / m_Timer;

        if (std::abs(fps - pastFps) > 0.1f)
        {
            auto textComp = GetOwner()->Get<TextComponent>();
            if (textComp) {
                textComp->SetText(std::format("{:.1f} FPS", fps));
            }
            pastFps = fps;
        }

        // 4. Reset counters
        m_Timer = 0.0f;
        m_FrameCount = 0;
    }
}

void dae::FPSComponent::Render() {
//////
}