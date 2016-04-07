#pragma once

#include <string>
#include <GL\glew.h>

namespace GraphicsLibrary
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexPath, const std::string& fragmentPath);
		void linkShaders();
		void addAttribute(const std::string& attributeName);
		void use() const;
		void unuse() const;
		GLint getUniformLocation(const std::string& uniformName) const;

	private:
		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const std::string& filePath, GLuint id) const;
	};
}