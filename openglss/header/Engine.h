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
    private:
        GLFWwindow *window;

        GLuint shader;
        GLuint VertexArrayID;
        GLuint vertexbuffer;

        std::vector<atom::Model> models;

    public:
        Engine();
        void initWindow(int w, int h, const char *title);
        void loop();
        ~Engine();
    };
}

#endif