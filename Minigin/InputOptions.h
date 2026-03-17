#pragma once

namespace dae {

enum class InputState
{
	JustPressed,
	JustReleased,
	Pressed,
};

enum class InputKeybinds //how calc from XINput to normal input????
{
	//keyboard inputs
	KEYBOARD_BEGIN,
	W,
	A,
	S,
	D, //for walk
	E,
	F,
	Z, //button used for spray
	X, //also used for spray
	KEYBOARD_END,

	//controller inputs
	CONTROLLER_BEGIN,
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

	BUTTON_SOUTH,
	BUTTON_EAST,
	BUTTON_WEST,
	BUTTON_NORTH,
	CONTROLLER_END,
};
}
