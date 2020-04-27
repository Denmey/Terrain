#pragma once

class InputManager;
class Window;
class Time;

#include "InputManager.hpp"
#include "Time.hpp"
#include "Window.hpp"

namespace Trn {
	extern InputManager input;
	extern Time &time;
	extern Window window;
}  // namespace Trn
