#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	currentScene->Update();
}

void dae::SceneManager::DelayUpdate()
{
	currentScene->DelayUpdate();
}

void dae::SceneManager::Render()
{
	currentScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(std::function<void(Scene* thisScene)> loadingFunction, const std::string& id)//EACH ID HAS TO BE ORIGINAL
{
	m_scenes.emplace_back(new Scene(loadingFunction), id); //why is there new here????
	if (m_scenes.size() == 1)
	{
		currentScene = m_scenes[0].first.get();
	}
	return *m_scenes.back().first;
}

void dae::SceneManager::SetScene(const std::string& id)
{
	for (auto& scene : m_scenes)
	{
		if (scene.second == id)
		{
			//load first scene
			scene.first->LoadScene();
			currentScene->RemoveAll();
			currentScene = scene.first.get();
			break; //don't need to continue loop if already found :)
		}
	}
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{
	for (auto& scene : m_scenes)
	{
		if (scene.second == name)
		{
			//load first scene
			return scene.first.get();

		}
	}

	return nullptr; //safety, shouldn't happen
}