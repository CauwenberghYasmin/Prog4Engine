
#include "KeyboardInput.h"
#include <SDL3/SDL.h>
#include "Binding.h"
#include "Command.h"
#include "InputOptions.h"

namespace dae {


void KeyboardInput::ProcessInput()
{
	m_PreviousState = m_CurrentState;
	m_CurrentState = SDL_GetKeyboardState(nullptr);

	for (auto& binding : m_Bindings)
	{
		if (binding->m_TriggerState == InputState::JustPressed && WasPressedThisFrame(binding->m_KeyBind)) 
			binding->m_Command->Execute();

		if (binding->m_TriggerState == InputState::JustReleased && WasReleasedThisFrame(binding->m_KeyBind)) 
			binding->m_Command->Execute();

		if (binding->m_TriggerState == InputState::Pressed && IsButtonPressed(binding->m_KeyBind))
			binding->m_Command->Execute();
	}
}


void KeyboardInput::AddBinding(std::unique_ptr<Command>&& command, SDL_Scancode keybind, InputState triggerState)
{
	//int scancode = ConvertToScancode(keybind); //make convertor and put it in the function below!!
	m_Bindings.emplace_back(std::make_unique<Binding>(std::move(command), keybind, triggerState));
}

bool KeyboardInput::WasPressedThisFrame(unsigned int button) const
{
	if (m_PreviousState == nullptr)
		return m_CurrentState[button];

	bool didButtonChange = m_CurrentState[button] ^ m_PreviousState[button];
	return didButtonChange && m_CurrentState[button];
}

bool KeyboardInput::IsButtonPressed(unsigned int button) const
{
	return m_CurrentState[button];
}

bool KeyboardInput::WasReleasedThisFrame(unsigned int button) const
{
	if (m_PreviousState == nullptr)
		return !m_CurrentState[button];


	bool didButtonChange = m_CurrentState[button] ^ m_PreviousState[button];
	return didButtonChange && !m_CurrentState[button];
}



}