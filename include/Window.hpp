#pragma once

// #include <GL/glew.h>
#include <glad.h>
// GLAD Before GLFW
#include <GLFW/glfw3.h>

#include <functional>

#include "InputManager.hpp" // TODO: Delete
#include "Globals.hpp"

namespace Trn {
	// extern Trn::InputManager input; // TODO: Delete
	// extern Trn::Time& time;
	class Window {
	  public:
		struct Settings {
			const char* title = "Application";
			GLuint width = 800;
			GLuint height = 600;
			GLuint OGLVersionMajor = 4;
			GLuint OGLVersionMinor = 3;
			// GLFW_OPENGL_PROFILE profile = GLFW_OPENGL_CORE_PROFILE;
			decltype(GLFW_OPENGL_CORE_PROFILE) profile = GLFW_OPENGL_CORE_PROFILE;
			bool resizable = false;
			bool debug = false;
		};

		// Inits GLFW, glad and sets viewport to the window size.
		Window(const Settings& settings);
		~Window();

		void error(const char* text); // TODO: Move from here to logger
		void warning(const char* text);

		bool shouldClose();
		void pollEvents();
		void swapBuffers();

		// void run(); // TODO: Delete
		// void setRunCallback(std::function<void(void)>); 

		bool isCursorVisible() const;
		void setCursorVisible(bool value);

	  private:
		// std::function<void(void)> runCallback; // TODO: Delete
		GLFWwindow* window = nullptr;
		Settings settings;
	};
}  // namespace Trn
