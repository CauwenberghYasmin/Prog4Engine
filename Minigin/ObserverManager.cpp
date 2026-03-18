#include "ObserverManager.h"
#include "GameObject.h"
#include "Observer.h"


namespace dae {


void ObserverManager::AddObserver(GameObject* subject, IObserver* observer) {
    m_Map[subject].push_back(observer);
}

void ObserverManager::RemoveObserver(GameObject* subject, IObserver* observer) {
    auto it = m_Map.find(subject);

    if (it != m_Map.end()) {
        std::erase(it->second, observer);

        if (it->second.empty()) {
            m_Map.erase(it);
        }
    }
}


void ObserverManager::NotifyObserver(GameObject* subject, const Event& event) {
    auto it = m_Map.find(subject);

    // Only iterate if the subject actually has observers registered
    if (it != m_Map.end()) {
        for (auto& obs : it->second) {
            obs->Notify(event, subject);
        }
    }
}


}