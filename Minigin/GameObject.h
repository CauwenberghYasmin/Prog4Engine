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

		//make map?
		std::vector<std::pair<std::unique_ptr<Component>, float>> m_ComponentVector{}; //has polymorphism so all components can be added to it
		
		std::vector <std::unique_ptr<Component>> m_DeleteList{};
		//every component will have an id number so they can be easily found

	public:
		virtual void Update();
		virtual void DelayUpdate();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);



		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		

		void Remove(float id);
		std::unique_ptr <Component> Get(float id);
		bool Check(float id);



		template<typename T>
		void AddComponent(std::unique_ptr <T>&& pComponent) //only add with std::move!
		{
			static_assert(std::is_base_of_v<Component, T>, "T needs to inherit from component"); //check if inherits

			if (pComponent != nullptr)
			{
				float id{ pComponent->GetID() };
				m_ComponentVector.push_back(std::make_pair(std::move(pComponent), id));
			}
		}
	};
}
