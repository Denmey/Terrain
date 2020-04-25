#include "Globals.hpp"

namespace Trn {
	Window::Settings settings;
	Window window("OpenGL Window", settings);

	InputManager input;
	Time &time = Time::Instance();
}
