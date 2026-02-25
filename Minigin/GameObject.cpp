#include <string>
#include "GameObject.h"

#include <utility>
#include <vector>
#include "Component.h"
#include<algorithm>

dae::GameObject::~GameObject() = default;

void dae::GameObject::Render() const
{
	for (auto& i : m_ComponentVector)
	{
		i.first->Render();
	}
}

void dae::GameObject::Update()
{
	for (auto& i : m_ComponentVector)
	{
		i.first->Update();
	}
}

void dae::GameObject::DelayUpdate() //not actual delete, but remove from component vector
{
	
	if (m_DeleteList.size() == 0) return;

	m_ComponentVector.erase(std::remove_if(m_ComponentVector.end(), m_ComponentVector.begin(), //rbegin and rend doesn't work -> ask teachers!!
		[&](const auto& component) {
			return std::any_of(m_DeleteList.end(), m_DeleteList.begin(), [&](const auto& deleteID) {
				return deleteID == component.second;
				});
		}),
		m_ComponentVector.begin());	//iterating backwards over them

	m_DeleteList.clear();

}



void dae::GameObject::Remove(float id) //look into maybe properly removing the slots! 
{
	for (auto& component : m_ComponentVector)
	{
		if (component.second == id)
		{
			m_DeleteList.push_back(std::move(component.second)); //goes onto the delete list for the delayed update
			break; //don't need to continue loop if already found :)
		}
	}
	//add safety net here?
}



bool dae::GameObject::Check(float id)
{
	for (auto& i : m_ComponentVector)
	{
		if (i.second == id)
		{
			return true;
		}

	}
	return false;
}