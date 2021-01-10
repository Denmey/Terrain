#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Clock.hpp"
#include "Window.hpp"

namespace Trn {
	class BaseApplication {
	  public:
		BaseApplication(const Window::Settings& windowSettings = {});
		virtual ~BaseApplication() = default;
		BaseApplication(const BaseApplication&) = delete;
		BaseApplication& operator=(const BaseApplication&) = delete;

		void run();
		const Clock& getClock() const;

	  private:
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void end() = 0;

	  protected:
		Window window;
	};
}  // namespace Trn
