#ifndef __SIMPLESHADER__
#define __SIMPLESHADER__

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>

#include <iostream>

class SimpleShader
{
public:
	SimpleShader(const char* vertex, const char* fragment);
	~SimpleShader();

	void bind();
	void unbind();

	int getError() { return error; }

	GLint getUniform(const char* v) { return glGetUniformLocation(shaderProgram, v); }

private:
	std::string openFile(const char* path);
	int error;
	GLuint shaderProgram;

};


#endif