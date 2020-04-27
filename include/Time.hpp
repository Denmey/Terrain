#pragma once

// #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glad.h>

namespace Trn {
	class Window;
	class Time {
	  public:
		static Time& Instance() {
			static Time time;
			return time;
		}
		double getDeltaTime() const noexcept;
		double getTime() const noexcept;

	  private:
		Time() { lastTime = currentTime = glfwGetTime(); }
		~Time() {}
		Time(const Time&);
		Time& operator=(const Time&);

		void update();
		double lastTime, currentTime, deltaTime;

		friend class Window;
	};
}  // namespace Trn
