#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include<utility>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::unique_ptr<Component>> m_ComponentVector{}; //has polymorphism so all components can be added to it
		//every component will have an id number so they can be easily found

	public:
		virtual void Update();
		virtual void DelayUpdate();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddComponent(std::unique_ptr <Component>&& pComponent); //only add with std::move!
		void Remove();

		//remove
		//get
		//check, returns boolean


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};
}
