#include "Time.hpp"

namespace Trn {
	void Time::update() {
		lastTime = currentTime;
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
	}

	float Time::getDeltaTime() const noexcept {
		return deltaTime;
	}
	float Time::getTime () const noexcept {
		return currentTime;
	}
}
