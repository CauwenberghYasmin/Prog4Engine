#pragma once
#include <vector>
#include <windows.h>
#include <XInput.h>
#include <memory>
#include "InputOptions.h"
#include "Binding.h"

namespace dae {

	
	class Command;
	class ControllerInput
	{
	public:
		ControllerInput(unsigned int id); //can have max 4, use id to see which one it is

		void processInput();

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

		void AddBinding(std::unique_ptr<Command>&& command, int keybind, InputState triggerState);
		void RemoveBinding(Binding* pBinding);

	private:
		XINPUT_STATE m_CurrentState{};
		unsigned int m_ButtonsPressedThisFrame{};
		unsigned int m_ButtonsReleasedThisFrame{};

		unsigned int m_ControllerIndex{}; //max 4! 

		std::vector<std::unique_ptr<Binding>> m_pBindings{};
	};

}