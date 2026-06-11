#pragma once
#include <vector>
//#include <windows.h>
//#include <XInput.h>
#include <memory>
#include "InputOptions.h"
#include "Binding.h"
#include "ControllerInput.h"


namespace dae {
	
	class Command;
	class ControllerInput
	{
	public:
		ControllerInput(unsigned int id); //can have max 4, use id to see which one it is
		~ControllerInput();

		void processInput();

		[[nodiscard]]bool IsDownThisFrame(ControllerInputs button) const;
		[[nodiscard]]bool IsUpThisFrame(ControllerInputs button) const;
		[[nodiscard]]bool IsPressed(ControllerInputs button) const;

		void AddBinding(std::unique_ptr<Command>&& command, ControllerInputs keybind, InputState triggerState);
		void RemoveBinding(Binding* pBinding);

	private:
		class ControllerImpl; // The Pimpl declaration
		std::unique_ptr<ControllerImpl> m_pImpl;

		unsigned int m_ControllerIndex{}; //max 4! 

		std::vector<std::unique_ptr<Binding>> m_pBindings{};
	};

}