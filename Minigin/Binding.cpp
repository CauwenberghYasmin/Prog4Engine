#include "Binding.h"
#include <memory>


namespace dae 
{

Binding::Binding(std::unique_ptr<Command> command, int keyBind, InputState triggerState) : //add id to remove from binding?
	m_Command(std::move(command)),
	m_KeyBind(keyBind),
	m_TriggerState(triggerState)
{
}

}