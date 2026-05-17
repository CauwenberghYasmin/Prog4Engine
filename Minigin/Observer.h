#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"
#include "Component.h"


namespace dae {

enum class Event
{
	PlayerDies,
	//PlayerRecievesScore,
	//PlayerWinsFirstGame
};



struct IObserver
{
	IObserver() = default;
	virtual ~IObserver() = default;
	virtual void Notify(Event event, GameObject* actor) = 0;
};

class GameEvent : public IObserver //used for display
{
public:
	GameEvent(GameObject* listener); //component is the listener

	void Notify(Event event, GameObject* actor) override; //pass subject here
private:
	GameObject* m_pListener;
};

//ALSO ADD EVENT BUSS
//TYPE WHERE YOU DONT CASH ANYTHING
//YOU JUST ADD AN EXTRA PARAMETER IN NOTIFY
//EX: an enemy died, 100 points
//so it can update the score


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






}