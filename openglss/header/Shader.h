#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

namespace atom
{
    class Shader
    {
    private:
        GLuint program;

    public:
        char *vertexShaderPath;
        char *fragmentShaderPath;
        bool isComplied = false;
        Shader(char *vertexShaderPath, char *fragmentShaderPath);
        void compile();
        GLuint getProgram();
        Shader copy();
    };
}

#endif