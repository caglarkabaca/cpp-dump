#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Model.h"

namespace atom
{
    class Engine
    {
    public:
        GLFWwindow *window;

        GLuint shader;
        GLuint VertexArrayID;
        GLuint vertexbuffer;

        std::vector<atom::ObjModel *> models;
        std::vector<atom::ModelBlueprint> appendQueue;

        glm::mat4 Model = glm::mat4(1.f);
        glm::mat4 View;
        glm::mat4 Projection;

        bool client;

        Engine();
        void initWindow(int w, int h, const char *title);
        void loop();
        ~Engine();
    };
}

#endif