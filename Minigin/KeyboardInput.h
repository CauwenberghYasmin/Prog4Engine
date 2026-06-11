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

	[[nodiscard]] bool WasPressedThisFrame(unsigned int button) const;
	[[nodiscard]] bool IsButtonPressed(unsigned int button) const;
	[[nodiscard]] bool WasReleasedThisFrame(unsigned int button) const;

	void AddBinding(std::unique_ptr<Command>&& command, unsigned int keybind, InputState triggerState);

private:
	std::vector<bool> m_CurrentState;
	std::vector<bool> m_PreviousState;

	std::vector<std::unique_ptr<Binding>> m_pBindings;
};

}