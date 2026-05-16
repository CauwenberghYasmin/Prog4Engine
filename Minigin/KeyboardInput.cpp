
#include "KeyboardInput.h"
#include <SDL3/SDL.h>
#include "Binding.h"
#include "Command.h"
#include "InputOptions.h"

namespace dae {

void KeyboardInput::ProcessInput()
{
	int numKeys;
	m_CurrentState = SDL_GetKeyboardState(&numKeys);

	if (m_PreviousState.empty()) //for first very frame game!
	{
		m_PreviousState.assign(m_CurrentState, m_CurrentState + numKeys);
	}

	for (auto& binding : m_pBindings)		//FIX JUST PRESSED AND JUST RELEASED
	{
		if (binding->m_TriggerState == InputState::JustPressed && WasPressedThisFrame(binding->m_KeyBind)) 
			binding->m_Command->Execute();

		if (binding->m_TriggerState == InputState::JustReleased && WasReleasedThisFrame(binding->m_KeyBind)) 
			binding->m_Command->Execute();

		if (binding->m_TriggerState == InputState::Pressed && IsButtonPressed(binding->m_KeyBind))
			binding->m_Command->Execute();
	}

	m_PreviousState.assign(m_CurrentState, m_CurrentState + numKeys); //at end!
}


void KeyboardInput::AddBinding(std::unique_ptr<Command>&& command, SDL_Scancode keybind, InputState triggerState)
{
	m_pBindings.emplace_back(std::make_unique<Binding>(std::move(command), keybind, triggerState));
}

bool KeyboardInput::WasPressedThisFrame(unsigned int button) const
{
	return m_CurrentState[button] && !m_PreviousState[button];
}

bool KeyboardInput::IsButtonPressed(unsigned int button) const
{
	return m_CurrentState[button];
}

bool KeyboardInput::WasReleasedThisFrame(unsigned int button) const
{
	return !m_CurrentState[button] && m_PreviousState[button];
}



}