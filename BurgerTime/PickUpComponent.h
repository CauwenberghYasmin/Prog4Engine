//
// Created by yasmi on 6/13/2026.
//

#ifndef MINIGIN_PICKUPCOMPONENT_H
#define MINIGIN_PICKUPCOMPONENT_H


#pragma once
#include "Component.h"
#include <functional>

class PickUpComponent : public dae::Component
{
public:
    PickUpComponent(dae::GameObject* pOwner, int scoreValue, int id =0);

    void SetOnCollectCallback(std::function<void(dae::GameObject*)> callback);

    void Collect(dae::GameObject* collector);
    int GetScoreValue() const;

    void Update() override{};
    void Render() override{};

private:
    int m_ScoreValue{ 0 };
    bool m_IsCollected{ false };
    std::function<void(dae::GameObject*)> m_OnCollectCallback;
};


#endif //MINIGIN_PICKUPCOMPONENT_H
