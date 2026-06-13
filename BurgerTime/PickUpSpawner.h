//
// Created by yasmi on 6/13/2026.
//

#ifndef MINIGIN_PICKUPSPAWNER_H
#define MINIGIN_PICKUPSPAWNER_H
#include <string>
#include <vector>
#include "Component.h"
#include "Scene.h"
#include "glm/vec2.hpp"

inline static const std::string spritePathfries {"Fries.png"};
inline static const std::string spritePathHotIceCream {"IceCream.png"};

class PickUpSpawner final : public dae::Component { //spawn on map -> pick up all to go to next level!
public:
    PickUpSpawner(dae::GameObject* owner, std::vector<glm::vec2>positions, int amountItems, dae::Scene* scene, int id =0);


    void PickedUp(dae::GameObject* object);
    void Update() override;
    void Render() override{};
private:
    const int m_AmountItems;
    int m_CollectedItems{0};
};


#endif //MINIGIN_PICKUPSPAWNER_H
