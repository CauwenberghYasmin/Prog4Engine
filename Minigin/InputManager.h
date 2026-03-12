#pragma once
#include "Singleton.h"
#include <vector>


namespace dae
{
	class ControllerInput;
	class KeyboardInput;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		//bind command
		//unbind command

		//ControllerInput* GetControllerInput(int controllerIndex);
		//KeyboardInput* GetKeyboardInput();
	


		std::vector<ControllerInput>m_ControllerInput{};
		KeyboardInput* m_KeyboardInput{};
	};

}

//need controller/gamepad class?