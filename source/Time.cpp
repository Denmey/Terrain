#include "Time.hpp"

namespace Trn {
	void Time::update() {
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
	}

	double Time::getDeltaTime() const noexcept {
		return deltaTime;
	}
	double Time::getTime () const noexcept {
		return currentTime;
	}
}
