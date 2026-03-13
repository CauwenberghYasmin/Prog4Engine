#pragma once
#include "InputOptions.h"

namespace dae {



	//struct Inputstate;
	class Command;
	class Binding
	{
	public:
		explicit Binding(Command* command, int keyBind, InputState triggerState) : //add id to remove from binding?
			m_Command(command),
			m_KeyBind(keyBind),
			m_TriggerState(triggerState)
		{
		}

		~Binding() = default;

		//add rule of 5

	//do make them private with getter functions!
		InputState m_TriggerState{};
		Command* m_Command{}; //does not own ->so no delete!
		int m_KeyBind{};
	};

}