#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "GameObject.h"
#include "Observer.h"


namespace dae {


class ObserverManager final : public Singleton<ObserverManager>
{
public:
	ObserverManager() = default;
	~ObserverManager() = default;

	void AddObserver(GameObject* subject, std::unique_ptr<IObserver> observer);
	void RemoveObserver(GameObject* subject, IObserver* observer); //should this also be a unique ptr? the observe manager own them, so how pass?
	void NotifyObserver(GameObject* subject, const Event& event);

	void ClearAllObservers() {
		m_Map.clear();
	}

private:

	std::unordered_map<GameObject*, std::vector<std::unique_ptr<IObserver>>> m_Map{}; //see if polymorphism works with the parent struct
	friend class Singleton<ObserverManager>;

};

}

//https://en.cppreference.com/w/cpp/container/unordered_map.html
//https://stackoverflow.com/questions/28811479/c-unordered-map-using-templates
//-> look here if polymorphism doesn't work