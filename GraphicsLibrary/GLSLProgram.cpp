#include "GLSLProgram.h"
#include "Debug.h"
#include <vector>
#include <fstream>
#include <iostream>

namespace GraphicsLibrary
{
	GLSLProgram::GLSLProgram() : _numAttributes(0),
		_programID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0)
	{

	}

	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::compileShaders(const std::string& vertexPath, const std::string& fragmentPath)
	{
		_programID = glCreateProgram();

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
			GraphicsLibrary::Debug::FatalError("Vertex shader failed to be created!");

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
			GraphicsLibrary::Debug::FatalError("Fragment shader failed to be created!");

		compileShader(vertexPath, _vertexShaderID);
		compileShader(fragmentPath, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders()
	{
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, GL_INFO_LOG_LENGTH, &maxLength, &errorLog[0]);

			glDeleteProgram(_programID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			GraphicsLibrary::Debug::Log("Shaders failed to link!", GraphicsLibrary::ErrorType::Error);
			GraphicsLibrary::Debug::FatalError(&(errorLog[0]));
		}

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	void GLSLProgram::use() const
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void GLSLProgram::unuse() const
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}

	void GLSLProgram::compileShader(const std::string& filePath, GLuint id) const
	{
		std::ifstream shaderFile(filePath);
		if (shaderFile.fail()) {
			perror(filePath.c_str());
			GraphicsLibrary::Debug::FatalError("Failed to open " + filePath);
		}

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line))
		{
			fileContents += line + "\n";
		}

		shaderFile.close();

		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);

			GraphicsLibrary::Debug::Log("Shader " + filePath + " failed to compile!", GraphicsLibrary::ErrorType::Error);
			GraphicsLibrary::Debug::FatalError(&(errorLog[0]));
		}
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName) const
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			Debug::FatalError("Uniform " + uniformName + " not found in shader!");
		return location;
	}
}
