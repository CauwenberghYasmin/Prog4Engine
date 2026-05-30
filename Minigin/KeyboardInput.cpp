
#include "KeyboardInput.h"
#include <SDL3/SDL.h>
#include "Binding.h"
#include "Command.h"
#include "InputOptions.h"

namespace dae {

    class KeyboardInput::KeyboardImpl //this is a scopre resolution operator? (NO INHERITANCE YASMIN!!!)
    {                                 // it's like a nested class :0
        public:
            void Update()
            {
                int numKeys;
                const bool* currentStateRaw = SDL_GetKeyboardState(&numKeys);

                 if (m_PreviousState.empty()) //move to constructor!
                 {
                     m_CurrentState.assign(currentStateRaw, currentStateRaw + numKeys);
                     m_PreviousState = m_CurrentState;
                 }
                else
                {
                    m_PreviousState = m_CurrentState;
                    m_CurrentState.assign(currentStateRaw, currentStateRaw + numKeys);
                }
            }

            bool WasPressedThisFrame(unsigned int button) const { return m_CurrentState[button] && !m_PreviousState[button]; }
            bool IsButtonPressed(unsigned int button) const { return m_CurrentState[button]; }
            bool WasReleasedThisFrame(unsigned int button) const { return !m_CurrentState[button] && m_PreviousState[button]; }

        private:
            std::vector<bool> m_CurrentState;
            std::vector<bool> m_PreviousState;
    };

    KeyboardInput::KeyboardInput() : 
        m_pImpl(std::make_unique<KeyboardImpl>()) 
    {
    }


    KeyboardInput::~KeyboardInput() = default; //IN HERE AND NOT HEADER, OTHERWISE ERROR!!! (compiler doesn't know pimple thingy yet -> cant call delete smartpointer)

    void KeyboardInput::ProcessInput()
    {
        m_pImpl->Update();

        for (auto& binding : m_pBindings)
        {
            if (binding->m_TriggerState == InputState::JustPressed && WasPressedThisFrame(binding->m_KeyBind))
                binding->m_Command->Execute();

            if (binding->m_TriggerState == InputState::JustReleased && WasReleasedThisFrame(binding->m_KeyBind))
                binding->m_Command->Execute();

            if (binding->m_TriggerState == InputState::Pressed && IsButtonPressed(binding->m_KeyBind))
                binding->m_Command->Execute();
        }
    }

    void KeyboardInput::AddBinding(std::unique_ptr<Command>&& command, unsigned int keybind, InputState triggerState)
    {
        m_pBindings.emplace_back(std::make_unique<Binding>(std::move(command), keybind, triggerState));
    }

    bool KeyboardInput::WasPressedThisFrame(unsigned int button) const { return m_pImpl->WasPressedThisFrame(button); }
    bool KeyboardInput::IsButtonPressed(unsigned int button) const { return m_pImpl->IsButtonPressed(button); }
    bool KeyboardInput::WasReleasedThisFrame(unsigned int button) const { return m_pImpl->WasReleasedThisFrame(button); }


//REFERENCE CODE BEFORE PIMPLE

//void KeyboardInput::ProcessInput()
//{
//	int numKeys;
//	m_CurrentState = SDL_GetKeyboardState(&numKeys);
//
//	if (m_PreviousState.empty()) //for first very frame game!
//	{
//		m_PreviousState.assign(m_CurrentState, m_CurrentState + numKeys);
//	}
//
//	for (auto& binding : m_pBindings)		//FIX JUST PRESSED AND JUST RELEASED
//	{
//		if (binding->m_TriggerState == InputState::JustPressed && WasPressedThisFrame(binding->m_KeyBind)) 
//			binding->m_Command->Execute();
//
//		if (binding->m_TriggerState == InputState::JustReleased && WasReleasedThisFrame(binding->m_KeyBind)) 
//			binding->m_Command->Execute();
//
//		if (binding->m_TriggerState == InputState::Pressed && IsButtonPressed(binding->m_KeyBind))
//			binding->m_Command->Execute();
//	}
//
//	m_PreviousState.assign(m_CurrentState, m_CurrentState + numKeys); //at end!
//}
//
//
//void KeyboardInput::AddBinding(std::unique_ptr<Command>&& command, unsigned intkeybind, InputState triggerState)
//{
//	m_pBindings.emplace_back(std::make_unique<Binding>(std::move(command), keybind, triggerState));
//}
//
//bool KeyboardInput::WasPressedThisFrame(unsigned int button) const
//{
//	return m_CurrentState[button] && !m_PreviousState[button];
//}
//
//bool KeyboardInput::IsButtonPressed(unsigned int button) const
//{
//	return m_CurrentState[button];
//}
//
//bool KeyboardInput::WasReleasedThisFrame(unsigned int button) const
//{
//	return !m_CurrentState[button] && m_PreviousState[button];
//}



}