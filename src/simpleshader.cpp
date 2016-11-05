#include "simpleshader.h"

SimpleShader::SimpleShader(const char* vertex, const char* fragment):
	error(0)
{
	std::string vert = openFile(vertex);
	std::string frag = openFile(fragment);
	const char* v = vert.c_str();
	
	const char* f = frag.c_str();
	if(error == 1) return;
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &v, 0);
	glCompileShader(vertexShader);
	GLint success;
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		error = 2;
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &f, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		error = 2;
		return;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

SimpleShader::~SimpleShader()
{
	glDeleteProgram(shaderProgram);
}


void SimpleShader::bind()
{
	glUseProgram(shaderProgram);
	
}

std::string SimpleShader::openFile(const char* path)
{
	std::ifstream file(path);
	if(!file.is_open()) error = 1;
	std::stringstream s;
	std::string line;
	while(getline(file, line))
	{
		s << line << "\n";
	}

	file.close();

	return s.str(); 
}