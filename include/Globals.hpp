#pragma once

class InputManager;
class Window;
class Time;

#include "InputManager.hpp"
#include "Window.hpp"
#include "Time.hpp"

namespace Trn {
	extern InputManager input;
	extern Time &time;
	extern Window window;
}
