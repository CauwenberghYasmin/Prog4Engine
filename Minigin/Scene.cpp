#include <algorithm>
#include "Scene.h"
#include <cassert>

#include "CollisionComponent.h"
#include "renderComponent.h"

using namespace dae;

Scene::Scene(std::function<void(Scene* thisScene)> func): //passing function where the scene loads/initializes their objects
	loadingFunction(func)
{
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
	hasVecChanged = true;
}

void Scene::Remove(const GameObject& object)
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_objects.end()
	);
}

void Scene::RemoveAll() //like unload function! -> okay since if you set the new scene, you reinitialize all your items
{
	m_objects.clear();
	hasVecChanged = true;
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::DelayUpdate()
{
	for (auto& object : m_objects)
	{
		object->DelayUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


void Scene::LoadScene() {
	loadingFunction(this);
}

std::vector<GameObject*> Scene::GetCollisionObjects() {

	if (visibleObjects.empty() || hasVecChanged == true) //knows if there was a change
	{
		for (const auto& object : m_objects) {

			if (object->GetComponent<CollisionComponent>() != nullptr) {
				visibleObjects.emplace_back(object.get()); //false error, project still runs
			}
		}
		hasVecChanged = false;
	}

	return visibleObjects;
}