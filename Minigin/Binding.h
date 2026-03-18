#pragma once
#include "InputOptions.h"
#include "Command.h"
#include <memory>

namespace dae {



	//struct Inputstate;
	class Binding
	{
	public:
		Binding(std::unique_ptr<Command>&& command, int keyBind, InputState triggerState);

		~Binding() = default;

		//add rule of 5

	//do make them private with getter functions!
		InputState m_TriggerState{};
		std::unique_ptr<Command> m_Command{}; //does not own ->so no delete!
		int m_KeyBind{};
	};

}