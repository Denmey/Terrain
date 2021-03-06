#include "Mesh.hpp"

namespace Trn {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
	           std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}

	void Mesh::Draw(Shader shader) {
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		for (GLuint i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);  // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string name;
			Texture::Type type = textures[i].type;
			switch (type) {
				case Texture::Type::Diffuse:
					name = "texture_diffuse" + std::to_string(diffuseNr++);
					break;
				case Texture::Type::Specular:
					name = "texture_specular" + std::to_string(specularNr++);
					break;
				default:
					std::cerr << "Error: Texture type undefined?" << std::endl;
					exit(EXIT_FAILURE);
					break;
			}
			shader.set1f(("material." + name).c_str(), static_cast<float>(i));
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
		             GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0],
		             GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      (void*)offsetof(Vertex, TexCoords));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      (void*)offsetof(Vertex, Bitangent));

		glBindVertexArray(0);
	}

	void Mesh::move(glm::vec3 delta) {
		for (auto& i : vertices) {
			i.Position += delta;
		}

		// DELETE THIS FOR THE SAKE OF OPTIMIZATION
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
		             GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
}  // namespace Trn
