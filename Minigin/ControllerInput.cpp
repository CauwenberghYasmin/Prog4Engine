#pragma once
#include "ControllerInput.h"
#include <windows.h>
#include <XInput.h>
#include "Binding.h"
#include <memory>
#include "Command.h"

namespace dae
{
	ControllerInput::ControllerInput(unsigned int id) :
		m_ControllerIndex(id)
	{
	}

	void ControllerInput::processInput() //from the ppt
	{
		XINPUT_STATE previousState;

		CopyMemory(&previousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		XInputGetState(m_ControllerIndex, &m_CurrentState);
		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);


		for (auto& binding : m_pBindings) //else if statements, if one is true, the other won't be true anymore, right?
		{
			if (binding->m_TriggerState == InputState::JustPressed && IsDownThisFrame(binding->m_KeyBind))
				binding->m_Command->Execute();

			else if (binding->m_TriggerState == InputState::JustReleased && IsUpThisFrame(binding->m_KeyBind))
				binding->m_Command->Execute();

			else if (binding->m_TriggerState == InputState::Pressed && IsPressed(binding->m_KeyBind))
				binding->m_Command->Execute();
		}
	}

	void ControllerInput::addBinding(std::unique_ptr <Binding>&& pBinder)
	{
		m_pBindings.emplace_back(std::move(pBinder));
	}

	void ControllerInput::RemoveBinding(Binding* pBinding) //ask teacher if this is correct!!!
	{
		auto point = remove_if(m_pBindings.begin(), m_pBindings.end(),
			[&pBinding](std::unique_ptr<Binding>& bind) {
				return pBinding == bind.get();
			});
		m_pBindings.erase(point, m_pBindings.end());
	}


	//ppt!
	bool ControllerInput::IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}
	bool ControllerInput::IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}
	bool ControllerInput::IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

}