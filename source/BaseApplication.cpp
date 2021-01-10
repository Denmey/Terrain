#include "BaseApplication.hpp"

#include "Globals.hpp"

namespace Trn {
	BaseApplication::BaseApplication(const Window::Settings& windowSettings)
	    : window(windowSettings) {}

	void BaseApplication::run() {
		clock.update();  // Init clock

		start();

		while (!window.shouldClose()) {
			// TODO: IMGUI new frame

			clock.update();
			update();
			// TODO: Create entities manager, move through all entities and call update for each of
			// them here?

			// TODO: IMGUI render

			window.pollEvents();
			window.swapBuffers();
		}

		end();
	}

	const Clock& BaseApplication::getClock() const { return clock; }
}  // namespace Trn