#pragma once
#include <vector>
#include <windows.h>
#include <XInput.h>
#include <memory>

class Binding;
class ControllerInput
{
public: 
	ControllerInput(unsigned int id); //can have max 4, use id to see which one it is

	void processInput();

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

	void addBinding(std::unique_ptr <Binding>&& pBinder);
	void RemoveBinding(Binding* pBinding);

private:
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};

	unsigned int m_ControllerIndex{}; //max 4! 

	std::vector<std::unique_ptr<Binding>> m_pBindings{};
};