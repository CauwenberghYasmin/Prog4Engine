#pragma once


namespace dae
{
	class Component//make template so the parameter list can be anything
	{
	public:
		explicit Component(float id);
		virtual ~Component() = default;

		virtual void Render() = 0;
		virtual void Update() = 0;

		float GetID();

	private:
		float m_IdNumber; //can also be string
	}; //no actual parameters to pass yet, made more for polymorphism
}

//DO RULE OF 5