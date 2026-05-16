#pragma once

namespace dae {

enum class InputState
{
	JustPressed,
	JustReleased,
	Pressed,
};

//enum Direction { Up, Down, Left, Right };

enum class ControllerInputs
{
	DPAD_UP,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,

	START,
	BACK,
	LEFT_THUMB,
	RIGHT_THUMB,
	LEFT_SHOULDER,
	RIGHT_SHOULDER,

	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
};
}
