#include <SDL3/SDL.h>
#include "InputManager.h"
#include "ControllerInput.h"
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include <windows.h>
#include <XInput.h>
#include "KeyboardInput.h"
#include <assert.h>

namespace dae
{

	bool InputManager::ProcessInput()  //is a singleton, so we can call it from anywhere
	{
		for (auto& console : m_ControllerInput)
		{
			console.processInput();
		}
		m_KeyboardInput.ProcessInput();

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



	ControllerInput* InputManager::GetControllerInput(int controllerIndex)
	{
		assert(controllerIndex < 4 && "index has to be between 0 and 3"); //index between 0-3!

		return &m_ControllerInput[controllerIndex];
	}

	KeyboardInput* InputManager::GetKeyboardInput()
	{
		return &m_KeyboardInput;
	}

	//get state controller/keyboard
	//-> executes required command

}


