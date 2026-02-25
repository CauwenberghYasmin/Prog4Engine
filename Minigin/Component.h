#pragma once


namespace dae
{
	class GameObject;
	class Component//make template so the parameter list can be anything
	{
	public:
		explicit Component(GameObject* owner, int id);
		virtual ~Component() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;

		int GetID();
		GameObject* GetOwner() { return m_pOwner; }

	private:
		GameObject* m_pOwner;
		int m_IdNumber; //no unint32_t because I also want to be able to give in neg numbers 
	}; //no actual parameters to pass yet, made more for polymorphism
}

//DO RULE OF 5