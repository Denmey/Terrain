#pragma once

// #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glad.h>

#include <functional>
#include <tuple>

namespace Trn {
	enum class KeyState { Released, Pressed, DoublePressed };

	// TODO: Make singleton
	// TODO: Divide in keyboard and mouse managers
	class InputManager final {
	  public:
		void captureKeyCallback(GLFWwindow* window) const;
		void captureMouseCallback(GLFWwindow* window) const;

		//
		KeyState getKey(int key) const;
		bool isPressed(int key) const;

		//
		KeyState getMouseKey(int key) const;
		bool isMousePressed(int key) const;
		std::tuple<double, double> getMousePosition() const;
		std::tuple<double, double> getMouseDelta() const;
		void setCursorMoveCallback(std::function<void(double, double, double, double)> callback);

	  private:
		static constexpr double doublePressInterval = 0.5f;

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		KeyState previousState[GLFW_KEY_LAST] = {KeyState::Released};
		KeyState currentState[GLFW_KEY_LAST] = {KeyState::Released};
		double lastTimePressed[GLFW_KEY_LAST] = {0.0f};

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		KeyState prevMouseState[GLFW_MOUSE_BUTTON_LAST] = {KeyState::Released};
		KeyState mouseState[GLFW_MOUSE_BUTTON_LAST] = {KeyState::Released};
		double mouseLastTimePressed[GLFW_MOUSE_BUTTON_LAST] = {0.0f};

		static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void cursorEnterCallback(GLFWwindow* window, int entered);
		std::function<void(double, double, double, double)> cursorMoveCallback;
		bool init = false;
		double sensitivity = 0.01;
		double xpos, ypos;
		double xdelta, ydelta;
	};
}  // namespace Trn
