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



	//maybe change it so that notify passes the origin and the destination: (passes cook and the textobject:
	// needs cook to get the health (origin)
	// needs text to set the text (destination!))
	//=> this way we dont have the render issue!!!
	void GameEvent::Notify(Event event, GameObject* actor)
	{

		switch (event) {
		case Event::PlayerDies:
			int newHealth{ actor->GetComponent<HealthComponent>()->GetCurrentHealth() }; //need cook component
			std::string newText{ std::string("Amount Lives: " + std::to_string(newHealth)) }; //need text component
			actor->GetComponent <TextComponent>()->SetText(std::string(newText));
			break;
			//case Event::PlayerRecievesScore:
			//	break;
		}

	}

}

