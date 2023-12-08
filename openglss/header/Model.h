#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Vertex.h"

namespace atom
{
    struct ModelBlueprint
    {
        int id;
        std::string vertexShader;
        std::string fragmentShader;
        std::string obj;
    };
    typedef struct ModelBlueprint ModelBlueprint;
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
        glm::mat4 ModelMatrix = glm::mat4(1.f);

        glm::vec3 modelPosition = glm::vec3(0.f);
        glm::vec3 modelRotation = glm::vec3(0.f);

    public:
        Model(atom::Shader _shader, std::vector<atom::Vertex> buffer);
        void updatePosition();
        void draw(glm::mat4 &projection, glm::mat4 &view);
        // ~Model();
    };

    class ObjModel : public Model
    {
    private:
        std::vector<atom::Vertex> getBuffer(char *objPath);

    public:
        char *obj;
        ObjModel(atom::Shader _shader, char *objPath);
        void serialize(int id, char *buffer);
    };
}

#endif