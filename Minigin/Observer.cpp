
#include "Observer.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "ServiceLocator.h"
//#include "sdlsoundsystem.h"

namespace dae 
{


	GameEvent::GameEvent(GameObject* listener) :
		IObserver(), m_pListener(listener)
	{
	}


	void GameEvent::Notify(Event event, GameObject* actor)
	{

		switch (event) {
		case Event::PlayerDies:
			if (event == Event::PlayerDies)
			{
				HealthComponent* pHealth = actor->GetComponent<HealthComponent>();
				TextComponent* m_pTextComponent = m_pListener->GetComponent<TextComponent>(); //prefer to cash it somewhere, but it's all pretty hard coded here
																							 //not in constructor, since now it's gameobject and not component -> BETTER
				if (pHealth != nullptr && m_pTextComponent != nullptr)
				{
					int currentHealth = pHealth->GetCurrentHealth();

					std::string newText = "Amount Lives: " + std::to_string(currentHealth);
					m_pTextComponent->SetText(newText);

					ServiceLocator::get_sound_system().PlaySound(1, 50);
				}
			}

			//case Event::PlayerRecievesScore:
			//	break;
		}

	}

}


