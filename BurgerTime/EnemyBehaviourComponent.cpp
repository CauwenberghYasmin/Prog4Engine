#include "EnemyBehaviourComponent.h"
#include "EnemyState.h"
#include "GameObject.h"


EnemyBehaviourComponent::EnemyBehaviourComponent(dae::GameObject* pGameObject, EnemyTypes enemyType, std::vector<dae::GameObject*> players, int id):
Component(pGameObject, id), m_EnemyType(enemyType), m_Players(std::move(players))
{
}

void EnemyBehaviourComponent::SetStartState( std::unique_ptr<EnemyState> CurrentState) {
	m_pCurrentState = std::move(CurrentState);
	m_pCurrentState->OnEnter(GetOwner(), m_Players);
}

void EnemyBehaviourComponent::Update()
{
	if (m_pCurrentState)
	{
		std::unique_ptr<EnemyState> newState = m_pCurrentState->Update(GetOwner());
		if (newState != nullptr)
		{
			m_pCurrentState->OnExit(GetOwner());
			m_pCurrentState = std::move(newState);
			m_pCurrentState->OnEnter(GetOwner(), m_Players);
		}
	}
}
void EnemyBehaviourComponent::Render(){} //dont actuallly render here, the scene takes care of that!
