#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Trn {
	class Clock {
	  public:
		Clock();
		void update();
		double currentTime() const;
		double previousTime() const;
		double deltaTime() const;

	  private:
	  private:
		double m_currentTime = 0.0;
		double m_previousTime = 0.0;
		double m_deltaTime = 0.0;
	};
}  // namespace Trn