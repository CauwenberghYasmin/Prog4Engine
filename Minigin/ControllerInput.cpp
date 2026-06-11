
#include "ControllerInput.h"
#include "Binding.h"
#include <memory>
#include "Command.h"
#include "InputOptions.h"

#ifdef _WIN32
#include <windows.h>
#include <XInput.h>
#endif

namespace dae //MOSTLY PPT GO RECHECK IF CONFUSDE!!!!!
{

    class ControllerInput::ControllerImpl
    {
    public:
        void Update(unsigned int controllerIndex)
        {
#ifdef _WIN32
            CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
            ZeroMemory(&currentState, sizeof(XINPUT_STATE));

            XInputGetState(controllerIndex, &currentState);

            auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
            buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
            buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
#else
            (void)controllerIndex;
#endif
        }

        [[nodiscard]]bool IsDownThisFrame(ControllerInputs button) const
        {
#ifdef _WIN32
            return buttonsPressedThisFrame & ToXInput(button);
#else
            (void)button; //people without windows just shouldn't play my game sniff
            return false;
#endif
        }

        [[nodiscard]]bool IsUpThisFrame(ControllerInputs button) const
        {
#ifdef _WIN32
            return buttonsReleasedThisFrame & ToXInput(button);
#else
            (void)button;
            return false;
#endif
        }

        [[nodiscard]]bool IsPressed(ControllerInputs button) const
        {
#ifdef _WIN32
            return currentState.Gamepad.wButtons & ToXInput(button);
#else
            (void)button;
            return false;
#endif
        }

    private:
       
#ifdef _WIN32
        WORD ToXInput(ControllerInputs button) const
        {
            switch (button)
            {
            case ControllerInputs::DPAD_UP: return XINPUT_GAMEPAD_DPAD_UP;
            case ControllerInputs::DPAD_DOWN: return XINPUT_GAMEPAD_DPAD_DOWN;
            case ControllerInputs::DPAD_LEFT: return XINPUT_GAMEPAD_DPAD_LEFT;
            case ControllerInputs::DPAD_RIGHT: return XINPUT_GAMEPAD_DPAD_RIGHT;
            case ControllerInputs::BUTTON_A: return XINPUT_GAMEPAD_A;
            case ControllerInputs::BUTTON_B: return XINPUT_GAMEPAD_B;
            case ControllerInputs::BUTTON_X: return XINPUT_GAMEPAD_X;
            case ControllerInputs::BUTTON_Y: return XINPUT_GAMEPAD_Y;
            case ControllerInputs::START: return XINPUT_GAMEPAD_START;
            case ControllerInputs::BACK: return XINPUT_GAMEPAD_BACK;
            case ControllerInputs::LEFT_THUMB: return XINPUT_GAMEPAD_LEFT_THUMB;
            case ControllerInputs::RIGHT_THUMB: return XINPUT_GAMEPAD_RIGHT_THUMB;
            case ControllerInputs::LEFT_SHOULDER: return XINPUT_GAMEPAD_LEFT_SHOULDER;
            case ControllerInputs::RIGHT_SHOULDER: return XINPUT_GAMEPAD_RIGHT_SHOULDER;
            
            default: return 0;
            }
        }

        XINPUT_STATE currentState{};
        XINPUT_STATE previousState{};
        WORD buttonsPressedThisFrame{};
        WORD buttonsReleasedThisFrame{};
#endif
    };

 

    ControllerInput::ControllerInput(unsigned int id) :
    	m_pImpl(std::make_unique<ControllerImpl>()), m_ControllerIndex(id)
    {
    }



    ControllerInput::~ControllerInput() = default;

    void ControllerInput::processInput()
    {
        m_pImpl->Update(m_ControllerIndex);

        for (auto& binding : m_pBindings)
        {
            auto btn = static_cast<ControllerInputs>(binding->m_KeyBind);

            if (binding->m_TriggerState == InputState::JustPressed && IsDownThisFrame(btn))
                binding->m_Command->Execute();
            else if (binding->m_TriggerState == InputState::JustReleased && IsUpThisFrame(btn))
                binding->m_Command->Execute();
            else if (binding->m_TriggerState == InputState::Pressed && IsPressed(btn))
                binding->m_Command->Execute();
        }
    }

    void ControllerInput::AddBinding(std::unique_ptr<Command>&& command, ControllerInputs keybind, InputState triggerState)
    {
        m_pBindings.push_back(std::make_unique<Binding>(std::move(command), static_cast<int>(keybind), triggerState));
    }

    void ControllerInput::RemoveBinding(Binding* pBinding)
    {
        auto point = std::remove_if(m_pBindings.begin(), m_pBindings.end(),
            [&pBinding](std::unique_ptr<Binding>& bind) {
                return pBinding == bind.get();
            });
        m_pBindings.erase(point, m_pBindings.end());
    }

    void ControllerInput::RemoveAllBindings() {
        m_pBindings.clear();
    }

    bool ControllerInput::IsDownThisFrame(ControllerInputs button) const { return m_pImpl->IsDownThisFrame(button); }
    bool ControllerInput::IsUpThisFrame(ControllerInputs button) const { return m_pImpl->IsUpThisFrame(button); }
    bool ControllerInput::IsPressed(ControllerInputs button) const { return m_pImpl->IsPressed(button); }


}