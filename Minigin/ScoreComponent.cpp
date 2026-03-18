#include "ScoreComponent.h"
#include "GameObject.h"
#include "Component.h"

namespace dae {


ScoreComponent::ScoreComponent(GameObject* pGameObject, int id, int startingScore) //startingscore = 0
	:Component(pGameObject, id), m_CurrentScore(startingScore) //starting score in case scores get transferred through levels, etc.
{
}

int ScoreComponent::GetCurrentScore() { return m_CurrentScore;}

void ScoreComponent::AddScorePoints(int addScoreAmount)
{
	m_CurrentScore += addScoreAmount;
}


void ScoreComponent::LoseScorePoints(int amountToLose)
{
	m_CurrentScore -= amountToLose;
}


}