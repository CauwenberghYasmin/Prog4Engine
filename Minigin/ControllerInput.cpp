#pragma once
#include "ControllerInput.h"
#include <windows.h>
#include <XInput.h>


ControllerInput::ControllerInput(unsigned int id):
	m_ControllerIndex (id)
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



	//for (auto& binding : m_Bindings)
	{
		//execute bindings?
		//-> yeah when you call the bindings here, they will get executed!!!
		//use switch case? check whitch one is needed?
	}
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
