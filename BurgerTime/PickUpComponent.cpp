//
// Created by yasmi on 6/13/2026.
//

#include "PickUpComponent.h"



PickUpComponent::PickUpComponent(dae::GameObject* pOwner, int scoreValue, int id)
        : Component(pOwner, id), m_ScoreValue(scoreValue)
{
}


void PickUpComponent::SetOnCollectCallback(std::function<void(dae::GameObject*)> callback)
{
    m_OnCollectCallback = std::move(callback);
}

void PickUpComponent::Collect(dae::GameObject* collector) {
    if (m_IsCollected) return;
    m_IsCollected = true;


    if (m_OnCollectCallback) { //notify spawner
        m_OnCollectCallback(GetOwner());
    }

    if (collector) return; //CHECK IF NEED
}

int PickUpComponent::GetScoreValue() const { return m_ScoreValue; }