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

	private:
		float m_IdNumber;
	}; //no actual parameters to pass yet, made more for polymorphism
}