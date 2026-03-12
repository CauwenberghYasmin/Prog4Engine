#include <SDL3/SDL.h>
#include "InputManager.h"
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include <windows.h>
#include <XInput.h>
#include "ControllerInput.h"
#include "KeyboardInput.h"


bool dae::InputManager::ProcessInput()  //is a singleton, so we can call it from anywhere
{
	//for (auto& console: m_ControllerInput)
	{
		//m_ControllerInput[i].ProcessInput();
	}
	//m_KeyboardInput.ProcessInput();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {

		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

		}
		// etc...

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}
	return true;
}
//can make get functions for controllers, since it's a singleton and can call those anywhere

//ControllerInput* dae::InputManager::GetControllerInput(int controllerIndex)
//{
//	assert(controllerIndex < 4 && "only up to 4 controllers are supported, controllerIndex can not be bigger than 3");
//	return &m_ControllerInput[controllerIndex];
//}

//KeyboardInput* dae::InputManager::GetKeyboardInput()
//{
//	return &m_KeyboardInput;
//}



//get state controller/keyboard
//-> executes required command




