#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "InputManager.hpp"
#include "Time.hpp"

// TODO: Delete InputManager.cpp and Window.hpp externs

namespace Trn {
	extern Trn::InputManager input;
	extern Trn::Time &time;
	class Window {
	public:
		struct Settings {
			GLuint width = 800;
			GLuint height = 600;
			GLuint major = 3;
			GLuint minor = 3;
			// GLFW_OPENGL_PROFILE profile = GLFW_OPENGL_CORE_PROFILE;
			decltype(GLFW_OPENGL_CORE_PROFILE) profile = GLFW_OPENGL_CORE_PROFILE;
			bool resizable = false;
			bool debug = false;
		};

		// Inits GLFW, glad and sets viewport to the window size.
		Window(const char* name, const Settings& settings);
		~Window();

		void error(const char* text);
		void warning(const char* text);
		// void update();
		bool shouldClose();
		void pollEvents();
		void swapBuffers();
		void run();
		void setRunCallback(std::function<void(void)>);
		bool isCursorVisible() const;
		void setCursorVisible(bool value);
	private:
		std::function<void(void)> runCallback;
		GLFWwindow* window = nullptr;
		Settings settings;
	};
}
