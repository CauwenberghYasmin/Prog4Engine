#include <string>
#include <utility>
#include <vector>
#include "Component.h"
#include<algorithm>
#include "GameObject.h"

#include <glm/glm.hpp>

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
	
	if (m_DeleteListComponents.size() != 0)
	{
		m_ComponentVector.erase(std::remove_if(m_ComponentVector.end(), m_ComponentVector.begin(), //rbegin and rend doesn't work -> ask teachers!!
			[&](const auto& component) {
				return std::any_of(m_DeleteListComponents.end(), m_DeleteListComponents.begin(), [&](const auto& deleteID) {
					return deleteID == component.second;
					});
			}),
			m_ComponentVector.begin());	//iterating backwards over them

		m_DeleteListComponents.clear();
	}
	else if (m_DeleteListChildren.size() != 0)	//check if this lambda actually works!
	{
		m_pChildren.erase(std::remove_if(m_pChildren.end(), m_pChildren.begin(), //rbegin and rend doesn't work -> ask teachers!!
			[&](const auto& child) {
				return std::any_of(m_DeleteListChildren.end(), m_DeleteListChildren.begin(), [&](auto& toDeletChild) {
					return child == toDeletChild;
					});
			}),
			m_pChildren.begin());

		m_DeleteListChildren.clear();
	}

}



void dae::GameObject::Remove(float id) //look into maybe properly removing the slots! 
{
	for (auto& component : m_ComponentVector)
	{
		if (component.second == id)
		{
			m_DeleteListComponents.push_back(std::move(component.second)); //goes onto the delete list for the delayed update
			break; //don't need to continue loop if already found :)
		}
	}
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



dae::GameObject* dae::GameObject::GetParent()
{
	return m_pParent;
}

int dae::GameObject::GetChildCount()
{
	return static_cast<int>(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAtIndex(int index)
{
	return m_pChildren[index];
}


bool dae::GameObject::IsChild(GameObject* object)
{
	for (const auto& child : m_pChildren)
	{
		if (object == child)
			return true;
	}
	
	return false;
}


void dae::GameObject::AddChild(GameObject* child)
{
	if (child == nullptr || child->GetParent() == this)
		return;

	//update pos, rotation, scale
	child->GetParent()->RemoveChild(child);
	//child->SetParent(this, false); //not used to avoid stack overflow
	child->m_pParent = this;
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)//set parent to nullptr
{
	if (child == nullptr || !IsChild(child))
		return;

	//update pos, rotation, scale

	m_DeleteListChildren.emplace_back(child);
	//child->SetParent(this, false); not used to avoid stack overflow
	child->m_pParent = nullptr;
}



//from ppt -> look later into improving when more time
void dae::GameObject::SetParent(GameObject* newParent, bool keepWorldPosition)
{
	if (IsChild(newParent) || newParent == this || m_pParent == newParent)
		return;


	if (newParent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - newParent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = newParent;


	if (m_pParent) m_pParent->AddChild(this);
}




void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}


//here aswell from ppt
const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_positionIsDirty)
		UpdateWorldPosition();
	return m_worldPosition;
}



void dae::GameObject::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		if (m_pParent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_pParent->GetWorldPosition() + m_localPosition;
	}
	m_positionIsDirty = false;
}
