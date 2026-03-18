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
	IObserver() = default;
	virtual ~IObserver() = default;
	virtual void Notify(Event event, GameObject* actor) = 0;
};


//class Achievement : public IObserver
//{
//public:
//	void Notify(Event event, GameObject* actor) override
//	{
//		switch (event) {
//		case Event::PlayerWinsFirstGame:
//			//if (CheckIfNobodyElseDiedYet(actor)) {
//			//	Unlock(Achievement::FirstBlood);
//			//}
//			break;
//		}
//	}
//private:
//	void Unlock(Achievement achievement) {
//		// code to unlock an achievement...
//	}
//};


class GameEvent : public IObserver //used for display
{
public:
	GameEvent();

	void Notify(Event event, GameObject* actor) override;
private:
	//create TextObject here and make the observer draw it?
	//try cashing the component?
};




}