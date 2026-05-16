#pragma once
#include "Singleton.h"
#include "ControllerInput.h"
#include "KeyboardInput.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		
		ControllerInput* GetControllerInput(int controllerIndex);
		KeyboardInput* GetKeyboardInput();
	
	private:

		ControllerInput m_ControllerInput[2]{ 0, 1}; //we have max 2 plaeyrs
		KeyboardInput m_KeyboardInput{};
	};

}

//need controller/gamepad class?