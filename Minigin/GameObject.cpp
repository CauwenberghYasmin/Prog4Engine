#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <utility>
#include <vector>
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Render() const
{
	for (auto& i : m_ComponentVector)
	{
		i.first->Render();
	}

	if (m_texture != nullptr)	//draws game objects who don't have components
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::GameObject::Update()
{
	for (auto& i : m_ComponentVector)
	{
		i.first->Update();
	}
}
void dae::GameObject::DelayUpdate(){}


void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}


void dae::GameObject::Remove(float id) //look into maybe properly removing the slots! 
{
	for (auto& i : m_ComponentVector)
	{
		if (i.second == id)
		{
			i.second = INT16_MIN; //safety measures
			m_DeleteList.push_back(std::move(i.first)); //goes onto the delete list for the delayed update (TODO)
			i.first = nullptr;	//safety measures
			break;
		}
	}
	//add safety net here?
}

std::unique_ptr<dae::Component> dae::GameObject::Get(float id)
{
	for (auto& i : m_ComponentVector)
	{
		if (i.second == id)
		{
			return std::move(i.first); //check with teach if this smart, or to make is a shared pointer
		} //inside game object, might still use the pointer for other functions...? (like update?), or is that in their own derived class
		//can also return a raw pointer with .get, but then you need to make sure to always delete it!!
	}

	return nullptr; //safety net?
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