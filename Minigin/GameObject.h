#pragma once
//#include <string>
#include <memory>
//#include "Transform.h"
#include "Component.h"
#include <vector>
#include<utility>
#include <glm/glm.hpp>

namespace dae //emiscript works
{
	class Texture2D;
	class GameObject final
	{
		
		std::vector<std::pair<std::unique_ptr<Component>, int>> m_ComponentVector{}; //has polymorphism so all components can be added to it
		std::vector <int> m_DeleteListComponents{};
		std::vector <GameObject* > m_DeleteListChildren{}; //also delayed delete

		//every component will have an id number so they can be easily found

		GameObject* m_pParent{nullptr};
		std::vector<GameObject*> m_pChildren{};


		void AddChild(GameObject* child); //like set parent
		void RemoveChild(GameObject* child);//set parent to nullptr

		void SetPositionDirty() { m_positionIsDirty = true; }
		void UpdateWorldPosition();
		const glm::vec3& GetWorldPosition();

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		bool m_positionIsDirty{ false };


	public:

		void Update();
		void DelayUpdate();
		void Render() const;


		GameObject* GetParent();

		void SetParent(GameObject* newParent, bool keepWorldPosition);
		int GetChildCount();
		GameObject* GetChildAtIndex(int index);
		void SetLocalPosition(const glm::vec3& pos);

		bool IsChild(GameObject* object); //checks if is child from this parentObject
		glm::vec3 GetLocalPosition() { return m_localPosition; }
		//void SetLocalPosition(const glm::vec3& pos) { m_localPosition = pos; }


		void Remove(float id);
		bool Check(float id);


		template<typename T>
		void AddComponent(std::unique_ptr <T>&& pComponent) // the add function should set the owner, but you can only set the owner in the constructor.....
		{
			static_assert(std::is_base_of_v<Component, T>, "T needs to inherit from component"); //check if inherits

			if (pComponent != nullptr ) //can add extra check to see if id is already used -> separate function
			{
				int id{ pComponent->GetID() };
				m_ComponentVector.push_back(std::make_pair(std::move(pComponent), id));
			}
		}
		


		template<typename T>
		T* Get(int id)	//used most
		{
			for (auto& i : m_ComponentVector)
			{
				if (i.second == id)
				{
					return i.first.get(); //check with teach if this smart, or to make is a shared pointer
				} //inside game object, might still use the pointer for other functions...? (like update?), or is that in their own derived class
				//can also return a raw pointer with .get, but then you need to make sure to always delete it!!
			}

			return nullptr; //safety net?
		}


		template<typename T>
		T* Get()	//overloading, will be used less
		{
			for (auto& component : m_ComponentVector)
			{
				auto* rawPtr = component.first.get();
				if (rawPtr && typeid(*rawPtr) == typeid(T))
					return static_cast<T*>(rawPtr);				
			}
			return nullptr;
		}


		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		

	};
}
