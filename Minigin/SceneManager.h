#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"
#include <utility>
#include <string>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(std::function<void(Scene* thisScene)> loadingFunction, const std::string& id);
		void SetScene(const std::string& id); //also unloads previous scene
		[[nodiscard]] Scene* GetScene(const std::string& name) const; //find them back by name!

		[[nodiscard]] Scene* GetCurrentScene() const;

		void Update();
		void DelayUpdate();
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		Scene* currentScene {nullptr};
		std::string currentId;
		std::vector<std::pair<std::unique_ptr<Scene>, std::string>> m_scenes{};

		std::string m_SceneToLoad{};
	};
}
