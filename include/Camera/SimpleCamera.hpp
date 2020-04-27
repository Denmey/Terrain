#pragma once
#include "Camera.hpp"

class SimpleCamera : public Camera {
  public:
	SimpleCamera(glm::mat4 view, glm::mat4 projection) : Camera(view, projection) {}
	~SimpleCamera() = default;

  private:
};
