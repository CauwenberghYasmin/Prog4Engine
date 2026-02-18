#pragma once
#include "FpsComponent.h"
#include "GameTime.h"
#include "TextObject.h"
#include <format>

void dae::FPSComponent::Update()
{
	float dt = dae::GameTime::GetInstance().GetDeltaTime();
	fps = 1 / dt;

	textComp->SetText(std::format("FPS: {:.1f}", fps));
}


dae::FPSComponent::FPSComponent(std::unique_ptr<TextObject> textComponent):
	textComp{ std::move(textComponent) }
{
}

