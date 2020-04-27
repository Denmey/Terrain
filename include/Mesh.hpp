#pragma once

// #include <GL/glew.h>
#include <glad.h>

#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Shader.hpp"

namespace Trn {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct Texture {
		enum Type { Diffuse, Specular };
		GLuint id;
		Type type;
	};

	class Mesh {
	  public:
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		/*  Functions  */
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
		     std::vector<Texture> textures);

		void Draw(Shader shader);
		void move(glm::vec3 delta);

	  private:
		/*  Render data  */
		GLuint VAO, VBO, EBO;
		/*  Functions    */
		void setupMesh();
	};
}  // namespace Trn
