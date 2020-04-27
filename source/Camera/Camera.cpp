#include "Camera/Camera.hpp"

#include <iostream>

std::tuple<glm::mat4, glm::mat4> Camera::getMatrices() const {
	return std::make_tuple(this->view, this->projection);
}
