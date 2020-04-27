#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Trn {
	Shader::Shader() {}

	void Shader::del() { glDeleteProgram(programID); }

	GLuint Shader::use() {
		glUseProgram(programID);
		// glLinkProgram(programID);
		GLenum err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cerr << "Error was detected in Shader::use() function: " << err << std::endl;
		}

		return programID;
	}

	GLuint Shader::getID() { return programID; }

	void Shader::addAttribute(const GLchar* attributeName, GLint size, GLenum type,
	                          GLboolean shouldBeNormalized, GLsizei stride, const GLvoid* offset) {
		GLint attrib = glGetAttribLocation(programID, attributeName);
		// std::cout << "Attrib location: " << attrib << std::endl;
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, size, type, shouldBeNormalized, stride, offset);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cerr << "Error was detected in Shader::addAttribute(" << attributeName
			          << ") function: " << err << std::endl;
		}
	}

	void Shader::setMat4(const GLchar* name, const glm::mat4& arg) {
		GLint uniform = getUniform(name);
		glUniformMatrix4fv(uniform, 1, GL_FALSE, &arg[0][0]);
	}
	void Shader::set1f(const GLchar* name, const float& arg) {
		GLint uniform = getUniform(name);
		glUniform1f(uniform, arg);
	}
	void Shader::set3f(const GLchar* name, const glm::vec3& arg) {
		GLint uniform = getUniform(name);
		glUniform3fv(uniform, 1, &arg[0]);
	}
	void Shader::set4f(const GLchar* name, const glm::vec4& arg) {
		GLint uniform = getUniform(name);
		glUniform4fv(uniform, 1, &arg[0]);
	}
	void Shader::set1i(const GLchar* name, const int arg) {
		GLint uniform = getUniform(name);
		glUniform1i(uniform, arg);
	}
	GLint Shader::getUniform(const GLchar* name) {
		GLint uniformID = glGetUniformLocation(programID, name);
		if (uniformID == -1) {
			std::cerr << "Can't get uniform \"" << name << "\" in Shader::getUniform" << std::endl;
			// exit(EXIT_FAILURE);
		}
		return uniformID;
	}

	void Shader::loadFromFile(const std::string& vertexFile, const std::string& fragmentFile,
	                          const std::string& geometryFile) {
		std::stringstream vertexSource, fragmentSource, geometrySource;
		// TODO: Add warning if source is empty
		try {
			std::ifstream vertFStr(vertexFile), fragFStr(fragmentFile), geomFStr;
			vertexSource << vertFStr.rdbuf();
			fragmentSource << fragFStr.rdbuf();
			vertFStr.close();
			fragFStr.close();

			if (geometryFile != "") {
				geomFStr.open(geometryFile);
				geometrySource << geomFStr.rdbuf();
				geomFStr.close();
				loadFromMemory(vertexSource.str().c_str(), fragmentSource.str().c_str(),
				               geometrySource.str().c_str());
			} else {
				loadFromMemory(vertexSource.str().c_str(), fragmentSource.str().c_str());
			}
		} catch (std::ifstream::failure& e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
	}
	void Shader::loadFromMemory(const GLchar* vertexSource, const GLchar* fragmentSource,
	                            const GLchar* geometrySource) {
		// Delete previous shader
		glDeleteProgram(programID);

		// Create and compile the vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		checkCompileErrors(vertexShader, "VERTEX");

		// Create and compile the fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");

		// Create and compile the geometry shader
		GLuint geometryShader = 0;
		if (geometrySource != nullptr) {
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &geometrySource, NULL);
			glCompileShader(geometryShader);
			checkCompileErrors(geometryShader, "GEOMETRY");
		}

		// Create and link shader program
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		if (geometrySource != nullptr) glAttachShader(shaderProgram, geometryShader);
		glLinkProgram(shaderProgram);
		checkCompileErrors(shaderProgram, "PROGRAM");

		programID = shaderProgram;

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometrySource != nullptr) {
			glDeleteShader(geometryShader);
		}
	}
	void Shader::checkCompileErrors(GLuint object, std::string type) {
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				          << infoLog
				          << "\n -- --------------------------------------------------- -- "
				          << std::endl;
			}
		} else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 1024, NULL, infoLog);
				std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				          << infoLog
				          << "\n -- --------------------------------------------------- -- "
				          << std::endl;
			}
		}
	}
}  // namespace Trn
