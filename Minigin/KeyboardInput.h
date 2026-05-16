#pragma once
#include "InputOptions.h"
#include <memory>
#include <vector>

namespace dae {


class Command;
class Binding;
class KeyboardInput {
public:
	KeyboardInput();
	~KeyboardInput();

	void ProcessInput();

	bool WasPressedThisFrame(unsigned int button) const;
	bool IsButtonPressed(unsigned int button) const;
	bool WasReleasedThisFrame(unsigned int button) const;

	void AddBinding(std::unique_ptr<Command>&& command, unsigned int keybind, InputState triggerState);

private:
	//checkExist()
	class KeyboardImpl;
	std::unique_ptr<KeyboardImpl> m_pImpl;

	//std::vector<Uint8> m_PreviousState; //apparently arrya and not pointer???
	//const bool* m_CurrentState = nullptr;

	std::vector<std::unique_ptr<Binding>> m_pBindings;
};

}