#pragma once
#include "InputOptions.h"

//struct Inputstate;
class Command;
class Binding
{
public:
	explicit Binding(Command* command, int keyBind, InputState triggerState): //add id to remove from binding?
		m_Command (command),
		m_KeyBind (keyBind),
		m_TriggerState(triggerState)
	{
	}

	~Binding() = default;

	//add rule of 5

private:
	Command* m_Command{}; //does not own ->so no delete!
	int m_KeyBind{};
	InputState m_TriggerState{};
};