// Prob can delete this
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Window.hpp"

#include "Camera/SimpleCamera.hpp"
#include "ControllableCamera.hpp"

#include <iostream>
#include <vector>
#include <memory>

// using std::vector;

// generate triangle mesh
Trn::Mesh getTriangleMesh(glm::vec3 positions[3]) {
	std::vector<Trn::Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Trn::Texture> textures;
	Trn::Vertex vertex;
	for (GLuint i = 0; i < 3; ++i) {
		vertex.Position = positions[i];
		vertices.push_back(vertex);
		indices.push_back(i);
	}

	return Trn::Mesh(vertices, indices, textures);
}

// TODO: Controllables manager
std::shared_ptr<Controllable> activeControllable;

// TODO: Cameras manager
std::shared_ptr<Camera> activeCamera;


int main() {
	// Init shaders and camera
	Trn::Shader basicShader;
	basicShader.loadFromFile("./Shaders/Basic.vert", "./Shaders/Basic.frag");
	basicShader.use();
	auto controllableCamera = std::make_shared<ControllableCamera>(glm::vec3(0.0, 0.0, -1.0), 3.14/2);
	activeControllable = controllableCamera;
	activeCamera = controllableCamera;
	Trn::input.setCursorMoveCallback([](double xpos, double ypos, double xdelta, double ydelta){
		activeControllable->processMouse(xdelta, ydelta);
	});
	Trn::window.setCursorVisible(false);

	// Init renderable object
	glm::vec3 points[3] = {glm::vec3(0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)};
	auto triangle = getTriangleMesh(points);
	triangle.move({0.0f, 0.0f, 1.0f});

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Trn::window.setRunCallback([&triangle, &basicShader](){
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		basicShader.use();
		// How to use already declared variables?
		auto [view, proj] = activeCamera->getMatrices();
		auto transf = glm::mat4(1.0);

		basicShader.setMat4("view", view);
		basicShader.setMat4("proj", proj);
		basicShader.setMat4("transf", transf);
		triangle.Draw(basicShader);
		// TODO: Get rid of double code in main.cpp and ControllableCamera.processKey
		for (int key = 0; key < GLFW_KEY_LAST; ++key) {
			if (Trn::input.isPressed(key)) {
				activeControllable->processKey(key, Trn::time.getDeltaTime());
			}
		}
	});
	Trn::window.run();

	return 0;
}
