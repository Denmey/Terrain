#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera/Camera.hpp"
#include "Controllable/Controllable.hpp"
#include "Globals.hpp"

class ControllableCamera : public Camera, public Controllable {
  public:
	// Angle in radians
	ControllableCamera(glm::vec3 pos, float angle)
	    : Camera(glm::lookAt(pos, pos + glm::vec3(glm::cos(angle), 0.0f, glm::sin(angle)),
	                         glm::vec3(0.f, 1.f, 0.f)),
	             glm::perspective(45.0, 1.0, 0.1, 100.0)),
	      pos(pos),
	      up(glm::vec3(0.0f, 1.0f, 0.0f)) {
		this->forward = glm::normalize(glm::vec3(glm::cos(angle), 0.0f, glm::sin(angle)));
		this->right = glm::normalize(glm::cross(forward, up));
		this->yaw = angle;
	}
	// TODO: Get rid of double code in main.cpp and ControllableCamera.processKey
	void processKey(int key, float deltaTime) override {
		// TEE(key);
		if (Trn::input.isPressed(GLFW_KEY_W)) {
			pos += forward * speed * deltaTime;
		} else if (key == GLFW_KEY_S) {
			pos -= forward * speed * deltaTime;
		}
		if (key == GLFW_KEY_D) {
			pos += right * speed * deltaTime;
		} else if (key == GLFW_KEY_A) {
			pos -= right * speed * deltaTime;
		}
		view = glm::lookAt(pos, pos + forward, up);
	}

	void processMouse(float xoffset, float yoffset) override {
		yaw = glm::mod(yaw + xoffset, 2 * glm::pi<float>());
		pitch -= yoffset;
		constexpr float almostPI = 1.56f;
		if (pitch > almostPI) {
			pitch = almostPI;
		} else if (pitch < -almostPI) {
			pitch = -almostPI;
		}
		forward
		    = {glm::cos(yaw) * glm::cos(pitch), glm::sin(pitch), glm::sin(yaw) * glm::cos(pitch)};
		forward = glm::normalize(forward);
		right = glm::normalize(glm::cross(forward, up));
		view = glm::lookAt(pos, pos + forward, up);
	}

  private:
	static constexpr float speed = 0.5f;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
	float pitch = 0, yaw;
};
