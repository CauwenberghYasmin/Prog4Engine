#pragma once
#include "Observer.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextObject.h"

namespace dae 
{


	GameEvent::GameEvent() :
		IObserver()
	{
	}



	void GameEvent::Notify(Event event, GameObject* actor)
	{

		switch (event) {
		case Event::PlayerDies:
			int newHealth{ actor->GetComponent<HealthComponent>()->GetCurrentHealth() };
			std::string newText{ std::string("Amount Lives: " + std::to_string(newHealth)) };
			actor->GetComponent <TextComponent>()->SetText(std::string(newText));
			//actor->->GetComponent <TextComponent>()->SetText(std::string(newText));
			break;
			//case Event::PlayerRecievesScore:
			//	break;
		}

	}

}