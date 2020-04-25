#include "InputManager.hpp"
#include "tee.hpp"

// #include <iostream>

namespace Trn {
	// TODO: Delete InputManager.cpp and Window.hpp externs
	extern InputManager input;

	void InputManager::captureKeyCallback(GLFWwindow *window) const {
		glfwSetKeyCallback(window, this->keyCallback);
	}

	void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		// InputManager *pInputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (action == GLFW_PRESS) {
			input.previousState[key] = input.currentState[key];
			float currentTime = glfwGetTime();
			float timeDiff = currentTime - input.lastTimePressed[key];
			// using std::cout;
			// using std::endl;
			if ((timeDiff < input.doublePressInterval) && input.previousState[key] == KeyState::Released) {
				// cout << "DOUBLE PRESSED " << key << " WITH TIME INTERVAL " << timeDiff << endl;
				input.currentState[key] = KeyState::DoublePressed;
			} else {
				// cout << "PRESSED ONCE " << key << endl;
				input.currentState[key] = KeyState::Pressed;
			}
		}
		if (action == GLFW_RELEASE) {
			// std::cout << "RELEASED " << key << std::endl;
			input.previousState[key] = input.currentState[key];
			input.currentState[key] = KeyState::Released;
			input.lastTimePressed[key] = glfwGetTime();
		}
	}

	void InputManager::captureMouseCallback(GLFWwindow *window) const {
		glfwSetCursorPosCallback(window, this->cursorPosCallback);
		glfwSetMouseButtonCallback(window, this->mouseButtonCallback);
		glfwSetCursorEnterCallback(window, this->cursorEnterCallback);
	}

	void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
		if (!input.init) {
			input.xpos = xpos;
			input.ypos = ypos;
			input.init = true;
			return;
		}
		input.xdelta = xpos - input.xpos;
		input.ydelta = ypos - input.ypos;
		input.xpos = xpos;
		input.ypos = ypos;
		if (input.cursorMoveCallback) {
			input.cursorMoveCallback(xpos, ypos, input.xdelta * input.sensitivity, input.ydelta * input.sensitivity);
		}
	}

	void InputManager::setCursorMoveCallback(std::function<void(double, double, double, double)> callback) {
		this->cursorMoveCallback = callback;
	}

	void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			input.prevMouseState[button] = input.mouseState[button];
			float currentTime = glfwGetTime();
			float timeDiff = currentTime - input.mouseLastTimePressed[button];
			if ((timeDiff < input.doublePressInterval) && input.prevMouseState[button] == KeyState::Released) {
				input.mouseState[button] = KeyState::DoublePressed;
			} else {
				input.mouseState[button] = KeyState::Pressed;
			}
		}
		if (action == GLFW_RELEASE) {
			input.prevMouseState[button] = input.mouseState[button];
			input.mouseState[button] = KeyState::Released;
			input.mouseLastTimePressed[button] = glfwGetTime();
		}
	}

	void InputManager::cursorEnterCallback(GLFWwindow* window, int entered) {
		if (!entered) {
			input.init = false;
		}
	}

	KeyState InputManager::getKey(int key) const {
		return currentState[key];
	}

	bool InputManager::isPressed(int key) const {
		auto state = currentState[key];
		return state == KeyState::Pressed || state == KeyState::DoublePressed;
	}

	KeyState InputManager::getMouseKey(int key) const {
		return this->mouseState[key];
	}
	bool InputManager::isMousePressed(int key) const {
		auto state = mouseState[key];
		return state == KeyState::Pressed || state == KeyState::DoublePressed;
	}
	std::tuple<double, double> InputManager::getMousePosition() const {
		return std::make_tuple(xpos, ypos);
	}
	std::tuple<double, double> InputManager::getMouseDelta() const {
		return std::make_tuple(xdelta * sensitivity, ydelta * sensitivity);
	}
}
