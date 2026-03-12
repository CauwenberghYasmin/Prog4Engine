#pragma once
#include "InputOptions.h"

//struct Inputstate;
class Command;
class Binding
{
public:
	Binding(Command* command, int keyBind, InputState triggerState):
		m_Command (command),
		m_KeyBind (keyBind),
		m_TriggerState(triggerState)
	{
	}




private:
	Command* m_Command{}; //does not own ->so no delete!
	int m_KeyBind{};
	InputState m_TriggerState{};
};