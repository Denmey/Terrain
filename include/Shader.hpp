#pragma once
// #include <GL/glew.h>
#include <glad.h>

#include <glm/glm.hpp>
#include <map>
#include <string>

namespace Trn {
	class Shader {
	  public:
		Shader();
		void del();

		GLuint use();
		GLuint getID();

		void loadFromFile(const std::string& vertexFile, const std::string& geometryFile,
		                  const std::string& fragmentFile = "");
		void loadFromMemory(const GLchar* vertexSource, const GLchar* geometrySource,
		                    const GLchar* fragmentSource = nullptr);

		void addAttribute(const GLchar* attributeName, GLint size, GLenum type,
		                  GLboolean shouldBeNormalized, GLsizei stride, const GLvoid* pointer);

		void setMat4(const GLchar* name, const glm::mat4& arg);
		void set3f(const GLchar* name, const glm::vec3& arg);
		void set4f(const GLchar* name, const glm::vec4& arg);
		void set1f(const GLchar* name, const float& arg);
		void set1i(const GLchar* name, const int arg);
		GLint getUniform(const GLchar* name);

	  private:
		void checkCompileErrors(GLuint object, std::string type);
		std::map<std::string, GLuint> attributes;
		std::map<std::string, GLuint> uniforms;
		GLuint programID = 0;
	};
}  // namespace Trn
