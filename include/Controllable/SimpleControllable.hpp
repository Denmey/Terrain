#pragma once

// TODO: delete
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Controllable.hpp"

class SimpleControllable : public Controllable {
public:
	SimpleControllable(glm::vec3 position, glm::vec3 forward, glm::vec3 up, Camera camera)
	// : Controllable(position, forward, up, camera)
	{
		(void)position;
		(void)forward;
		(void)up;
		(void)camera;
	}
	// virtual void update() override {
	//
	// }
	// virtual void processKey(int key) override {
	// 	if (key == GLFW_KEY_W) {
	// 		std::cout << "W is pressed" << std::endl;
	// 	}
	// }
};
