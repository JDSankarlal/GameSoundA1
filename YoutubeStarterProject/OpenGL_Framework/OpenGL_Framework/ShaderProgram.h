#pragma once

#include "GL\glew.h"
#include <MiniMath/Core.h>
#include <string>


class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	bool Load(const std::string &vertFile, const std::string &fragFile);
	bool isLoaded() const;
	//-Clear all data from OpenGL
	void UnLoad();
	bool LinkProgram();
	//Use / detach shader from use
	void Bind() const;
	void UnBind();

	void AddAttribute(unsigned int index, const std::string &attribName);

	//- Returns -1 if the attribute does not exist
	int GetAttribLocation(const std::string &attribName);
	//- Returns -1 if uniform does not exist
	int GetUniformLocation(const std::string &uniformName);

	//- Send Data to shaders
	void SendUniform(const std::string &name, int integer);
	void SendUniform(const std::string &name, unsigned int unsigned_integer);
	void SendUniform(const std::string &name, float scalar);
	void SendUniform(const std::string &name, const vec2 &vector);
	void SendUniform(const std::string &name, const vec3 &vector);
	void SendUniform(const std::string &name, const vec4 &vector);
	void SendUniformMat3(const std::string &name, float *matrix, bool transpose);
	void SendUniformMat4(const std::string &name, float *matrix, bool transpose);


private:
	bool _IsInit = false;
	GLuint _VertexShader	= 0;
	GLuint _FragShader		= 0;
	GLuint _Program			= 0;

	std::string ReadFile(const std::string &fileName) const;
	bool CompileShader(GLuint shader) const;
	void OutputShaderLog(GLuint shader) const;
	void OutputProgramLog() const;

};