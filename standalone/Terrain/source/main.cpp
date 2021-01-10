// Prob can delete this
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include <entt/entt.hpp>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "BaseApplication.hpp"
#include "Camera/SimpleCamera.hpp"
#include "ControllableCamera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Window.hpp"

// using std::vector;

// generate triangle mesh
Trn::Mesh getTriangleMesh() {
	glm::vec3 positions[3] = {glm::vec3(0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)};
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

static std::filesystem::path getResourcesPath(const std::filesystem::path& executablePath) {
	auto executableDirectory = executablePath.parent_path();
	auto resourcesPath = executableDirectory.append("Resources");
	return resourcesPath;
}

static std::filesystem::path subdir(const std::filesystem::path& dir, const std::string& subdir) {
	return std::filesystem::path(dir).append(subdir);
}

std::filesystem::path resOrigin;
class Application : public Trn::BaseApplication {
  private:
	Trn::Shader basicShader;
	std::shared_ptr<ControllableCamera> controllableCamera;
	Trn::Mesh triangle;

  public:
	Application(const Trn::Window::Settings& settings = {}) : triangle(getTriangleMesh()){};
	virtual void start() override {
		// Init shaders and camera
		basicShader.loadFromFile(subdir(resOrigin, "Shaders/Basic.vert").string(),
		                         subdir(resOrigin, "Shaders/Basic.frag").string());
		basicShader.use();
		controllableCamera
		    = std::make_shared<ControllableCamera>(glm::vec3(0.0, 0.0, -1.0), 3.14 / 2);
		activeControllable = controllableCamera;
		activeCamera = controllableCamera;

		Trn::input.setCursorMoveCallback(
		    [](double xpos, double ypos, double xdelta, double ydelta) {
			    activeControllable->processMouse(xdelta, ydelta);
		    });
		window.setCursorVisible(false);

		triangle.move({0.0f, 0.0f, 1.0f});

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	virtual void update() override {
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
				activeControllable->processKey(key, Trn::clock.deltaTime());
			}
		}
	}
	virtual void end() override {}
};

int main(int argc, char const* argv[]) {
	resOrigin = getResourcesPath(argv[0]);
	Application app;
	app.run();

	return 0;
}
