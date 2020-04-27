#pragma once

#include <glm/glm.hpp>

#include "../Camera/Camera.hpp"

class Controllable {
  public:
	// virtual void update() = 0;
	virtual void processKey(int key, float deltaTime) = 0;
	virtual void processMouse(float xoffset, float yoffset) = 0;
	void processMouse(glm::vec2 offset) { processMouse(offset.x, offset.y); }
	// virtual void doAction(const string& action, float deltaTime) = 0;
  protected:
	Controllable() = default;
	~Controllable() = default;
};
