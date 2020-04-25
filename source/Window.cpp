#include "Window.hpp"

#include <iostream>

namespace Trn {
	Window::Window(const char* name, const Settings& settings) {
		glfwSetErrorCallback([](int error, const char* description) {
			std::cerr << "Error: " << description << std::endl;
		});
		if (!glfwInit()) {
			error("Can't init GLFW");
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, settings.profile);
		glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.debug);
		window = glfwCreateWindow(settings.width, settings.height, name, NULL, NULL);
		if (window == NULL) {
			error("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK){
			error("Can't init glew");
		}

		glViewport(0, 0, settings.width, settings.height);
		// glfwSetWindowUserPointer(window, this);
		input.captureKeyCallback(window);
		input.captureMouseCallback(window);
	}

	void Window::error(const char* text) {
		std::cerr << "Error: "  << text << std::endl;
		if (window)
			glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	void Window::warning(const char* text) {
		std::cerr << "Warning: "  << text << std::endl;
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}

	void Window::pollEvents() {
		glfwPollEvents();
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(window);
	}

	Window::~Window() {
		if (window)
			glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::run() {
		while (!glfwWindowShouldClose(window)) {
			time.update();
			// TODO: Create entities manager, move through all entities and call update for each of them here.

			runCallback();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}

	void Window::setRunCallback(std::function<void(void)> callback) {
		runCallback = callback;
	}

	bool Window::isCursorVisible() const {
		throw "Not implemented";
	}
	void Window::setCursorVisible(bool value) {
		if (value) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}
