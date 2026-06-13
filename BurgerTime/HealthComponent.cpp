#include "HealthComponent.h"
#include "GameObject.h"
#include "Component.h"
#include "ObserverManager.h"

namespace dae {

HealthComponent::HealthComponent(GameObject* pGameObject, int startingHealth, int id):
	Component(pGameObject, id), m_StartHealth(startingHealth), m_CurrentHealth(startingHealth)
{
}




int HealthComponent::GetCurrentHealth()const
{
	return m_CurrentHealth;
}

bool HealthComponent::isDead()	const //will later properly add an event dispatcher when a player dies....?
{
	if (m_CurrentHealth == 0)
		return true;

	return false;
}

//void HealthComponent::DoDamage(int amountDamage)
//{
//	m_CurrentHealth -= amountDamage;
//
//	if (m_CurrentHealth < 0)
//		m_CurrentHealth = 0;
//}

void HealthComponent::ChangeHealth(int amountHealing)
{
	m_CurrentHealth += amountHealing;
	dae::ObserverManager::GetInstance().NotifyObserver(GetOwner(), Event::PlayerDies); //yes this is how to send stuff!
}

void HealthComponent::ResetHealth()
{
	m_CurrentHealth = m_StartHealth;
}


}