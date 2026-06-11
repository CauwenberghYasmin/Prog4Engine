#include "KeyboardInput.h"
#include <SDL3/SDL.h>
#include "Binding.h"
#include "Command.h"
#include "InputOptions.h"

namespace dae {

    KeyboardInput::KeyboardInput()
    {
        // init -> no crash
        int numKeys = 0;
        SDL_GetKeyboardState(&numKeys);
        m_CurrentState.resize(numKeys, false);
        m_PreviousState.resize(numKeys, false);
    }

    KeyboardInput::~KeyboardInput() = default;

    void KeyboardInput::ProcessInput()
    {
        int numKeys;
        const bool* keystate = SDL_GetKeyboardState(&numKeys);

        m_PreviousState = m_CurrentState;

        for (size_t i = 0; i < numKeys; i++) //std::copy doesn't work ->FIX THIS LATER, no raw forloops
        {
            m_CurrentState[i] = keystate[i];
        }

        for (auto& binding : m_pBindings)
        {
            auto key = static_cast<unsigned int>(binding->m_KeyBind);

            if (binding->m_TriggerState == InputState::JustPressed && WasPressedThisFrame(key))
                binding->m_Command->Execute();

            if (binding->m_TriggerState == InputState::JustReleased && WasReleasedThisFrame(key))
                binding->m_Command->Execute();

            if (binding->m_TriggerState == InputState::Pressed && IsButtonPressed(key))
                binding->m_Command->Execute();
        }
    }

    void KeyboardInput::AddBinding(std::unique_ptr<Command>&& command, unsigned int keybind, InputState triggerState)
    {
        m_pBindings.emplace_back(std::make_unique<Binding>(std::move(command), keybind, triggerState));
    }

    bool KeyboardInput::WasPressedThisFrame(unsigned int button) const
    {
        if (button >= m_CurrentState.size()) return false;
        return m_CurrentState[button] && !m_PreviousState[button];
    }

    bool KeyboardInput::IsButtonPressed(unsigned int button) const
    {
        if (button >= m_CurrentState.size()) return false;
        return m_CurrentState[button];
    }

    bool KeyboardInput::WasReleasedThisFrame(unsigned int button) const
    {
        if (button >= m_CurrentState.size()) return false;
        return !m_CurrentState[button] && m_PreviousState[button];
    }
}