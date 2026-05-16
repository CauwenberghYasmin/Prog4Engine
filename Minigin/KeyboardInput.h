#pragma once
#include "InputOptions.h"
#include <memory>
#include <vector>
#include <SDL3/SDL_scancode.h>

namespace dae {


class Command;
class Binding;
class KeyboardInput {
public:
	explicit KeyboardInput() = default;
	~KeyboardInput() = default;

	void ProcessInput();

	bool WasPressedThisFrame(unsigned int button) const;
	bool IsButtonPressed(unsigned int button) const;
	bool WasReleasedThisFrame(unsigned int button) const;

	void AddBinding(std::unique_ptr<Command>&& command, SDL_Scancode keybind, InputState triggerState);

private:
	//checkExist()

	std::vector<Uint8> m_PreviousState; //apparently arrya and not pointer???
	const bool* m_CurrentState = nullptr;

	std::vector<std::unique_ptr<Binding>> m_pBindings;
};

}