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
		//unbind command! -> only pushing out of binding vector or replace the trigger key?

		//ControllerInput* GetControllerInput(int controllerIndex);
		//KeyboardInput* GetKeyboardInput();
	


		//std::vector<ControllerInput>m_ControllerInput{}; //-> go over, set max to 4!!!
		KeyboardInput* m_KeyboardInput{};
	};

}

//need controller/gamepad class?