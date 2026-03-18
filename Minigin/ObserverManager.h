#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "GameObject.h"
#include "Observer.h"

//TO ALEX:
//I added the functionality like this because I couldn't figure out how to add/remove bindings 
// from a gameObject without adding the code in the cpp file
//-> which you're not supposed to do since not every object needs an observer
//please let me know in the feedback if this is incorrect/if there is a better way to do this :)


namespace dae {



class ObserverManager final : public Singleton<ObserverManager>
{
public:
	ObserverManager() = default;
	~ObserverManager() = default;

	void AddObserver(GameObject* subject, IObserver* observer);
	void RemoveObserver(GameObject* subject, IObserver* observer);
	void NotifyObserver(GameObject* subject, const Event& event);

private:

	std::unordered_map<GameObject*, std::vector<IObserver*>> m_Map{}; //see if polymorphism works with the parent struct
	friend class Singleton<ObserverManager>;

};

}

//https://en.cppreference.com/w/cpp/container/unordered_map.html
//https://stackoverflow.com/questions/28811479/c-unordered-map-using-templates
//-> look here if polymorphism doesn't work