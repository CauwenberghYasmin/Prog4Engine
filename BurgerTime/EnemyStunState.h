#pragma once
#include "EnemyState.h"
#include "GameObject.h"

//PEPPER SPRAY
class EnemyStunState final : public EnemyState
{
public:
    void OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players) override;
    void OnExit(dae::GameObject* pOwner) override;

    std::unique_ptr<EnemyState> Update(dae::GameObject* pOwner) override;

private:
    float m_StunTimer{ 3.0f };
};


inline static const std::string spritePathHotDog {"HotDog.png"};
inline static const std::string spritePathHotDogStunned {"HotDogSprayed.png"};
inline static const std::string spritePathEgg {"Egg.png"};
inline static const std::string spritePathEggStunned {"EggSprayed.png"};
inline static const std::string spritePathPickle{"Pickle.png"};
inline static const std::string spritePathPickleStunned{ "PickleSprayed.png"};