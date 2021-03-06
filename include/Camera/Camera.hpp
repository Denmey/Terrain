#pragma once
#include <glm/glm.hpp>
#include <tuple>

class Camera {
  public:
	Camera(glm::mat4 view, glm::mat4 projection) : view(view), projection(projection) {}
	virtual ~Camera() = default;
	std::tuple<glm::mat4, glm::mat4> getMatrices() const;

  protected:
	glm::mat4 view;
	glm::mat4 projection;
};
