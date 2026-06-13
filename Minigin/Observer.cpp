
#include "Observer.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PickUpComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "ServiceLocator.h"
//#include "sdlsoundsystem.h"

namespace dae {
	GameEvent::GameEvent(GameObject* listener) :
		IObserver(), m_pListener(listener)
	{
	}


	void GameEvent::Notify(Event event, GameObject* actor)
	{

		switch (event)
		{
			case Event::PlayerDies:
			{
				LevelManager::GetInstance().LoseLife();
				if (TextComponent* pText = m_pListener->GetComponent<TextComponent>())
				{
					int currentLives = LevelManager::GetInstance().GetLives();
					pText->SetText("Amount Lives: " + std::to_string(currentLives));
					ServiceLocator::get_sound_system().PlaySound(2, 200);

					if (LevelManager::GetInstance().GetLives() <= 0)
					{
						LevelManager::GetInstance().HighscoreLevel();
					}
				}
				break;
			}

			case Event::ItemPickedUp:
			{
				PickUpComponent* pPickup = actor->GetComponent<PickUpComponent>();
				if (pPickup != nullptr)
				{
					LevelManager::GetInstance().AddScore(pPickup->GetScoreValue());
					if (TextComponent* pText = m_pListener->GetComponent<TextComponent>())
					{
						int currentScore = LevelManager::GetInstance().GetScore();
						pText->SetText("Score: " + std::to_string(currentScore));
						ServiceLocator::get_sound_system().PlaySound(1, 50);
					}
				}
				break;
			}
		}



	}
}

