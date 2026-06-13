#pragma once
#include "EnemyState.h"

//when die by hamburger
class EnemyCrushedState final : public EnemyState
{
public:
	void OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players) override;
	void OnExit(dae::GameObject* pOwner) override;
	std::unique_ptr<EnemyState> Update(dae::GameObject* pOwner) override;


};