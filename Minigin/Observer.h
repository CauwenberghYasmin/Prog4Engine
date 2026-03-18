#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextObject.h"


namespace dae {

enum class Event
{
	PlayerDies,
	PlayerRecievesScore,
	PlayerWinsFirstGame
};



struct IObserver
{
	virtual ~IObserver() = default;
	virtual void Notify(Event event, GameObject* actor) = 0;
};


class Achievement : public IObserver
{
public:
	void Notify(Event event, GameObject* actor) override
	{
		switch (event) {
		case Event::PlayerWinsFirstGame:
			//if (CheckIfNobodyElseDiedYet(actor)) {
			//	Unlock(Achievement::FirstBlood);
			//}
			break;
		}
	}
private:
	void Unlock(Achievement achievement) {
		// code to unlock an achievement...
	}
};


class GameEvent : public IObserver //used for display
{
public:
	void Notify(Event event, GameObject* actor) override
	{
		switch (event) {
		case Event::PlayerDies:
			int newHealth{ actor->GetComponent<HealthComponent>()->GetCurrentHealth() };
			actor->GetComponent <TextComponent>()->SetText(std::string("Amount Lives: " + std::to_string(newHealth)));
			break;
		case Event::PlayerRecievesScore:
			break;
		}
	}
private:
	//create TextObject here and make the observer draw it?
};

}