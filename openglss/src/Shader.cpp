#include "Shader.h"

#include "utils.h"

#include <GL/glew.h>

atom::Shader::Shader(char *vertexShaderPath, char *fragmentShaderPath) : vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath) {}

void atom::Shader::compile()
{
    program = LoadShaders(vertexShaderPath, fragmentShaderPath);
    isComplied = true;
}
GLuint atom::Shader::getProgram() { return program; }

atom::Shader atom::Shader::copy()
{
    return Shader(vertexShaderPath, fragmentShaderPath);
}