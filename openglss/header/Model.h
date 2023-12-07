#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Vertex.h"

namespace atom
{
    class Model
    {
    private:
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        GLuint assigned_shader;
        int vertex_count;

    public:
        Model(GLuint shader, std::vector<atom::Vertex> buffer);
        void draw();
        // ~Model();
    };
}

#endif