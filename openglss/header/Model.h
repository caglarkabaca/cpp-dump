#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Shader.h"
#include "Vertex.h"

namespace atom
{
    class Model
    {
    public:
        GLuint VertexArrayID;
        GLuint vertexbuffer;
        std::vector<atom::Vertex> vertices;
        int vertex_count;
        atom::Shader shader;

        GLuint MVP;
        glm::mat4 mvp = glm::mat4(1.f);

    public:
        Model(atom::Shader _shader, std::vector<atom::Vertex> buffer);
        void draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
        // ~Model();
    };

    class ObjModel : public Model
    {
    private:
        std::vector<atom::Vertex> getBuffer(char *objPath);
        char *obj;

    public:
        ObjModel(atom::Shader _shader, char *objPath);
        void serialize(int id, char *buffer);
    };
}

#endif