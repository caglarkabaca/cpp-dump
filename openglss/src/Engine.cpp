#include "Engine.h"

#include "utils.h"

#include <cstdio>
#include <exception>
#include <stdexcept>
#include <vector>
#include <cstdlib>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define random_vec3() glm::vec3(std::rand() / static_cast<float>(RAND_MAX), std::rand() / static_cast<float>(RAND_MAX), std::rand() / static_cast<float>(RAND_MAX))

// init glfw
atom::Engine::Engine()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
};

void atom::Engine::initWindow(int w, int h, const char *title)
{
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (window == NULL)
    {
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.9255f, 0.9255f, 0.9255f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    shader = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");

    /* box

    std::vector<atom::Vertex> vertices{
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.583f,
            0.771f,
            0.014f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            1.0f,
            0.609f,
            0.115f,
            0.436f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            1.0f,
            0.327f,
            0.483f,
            0.844f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            -1.0f,
            0.822f,
            0.569f,
            0.201f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.435f,
            0.602f,
            0.223f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            -1.0f,
            0.310f,
            0.747f,
            0.185f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            1.0f,
            0.597f,
            0.770f,
            0.761f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.559f,
            0.436f,
            0.730f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            -1.0f,
            0.359f,
            0.583f,
            0.152f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            -1.0f,
            0.483f,
            0.596f,
            0.789f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            -1.0f,
            0.559f,
            0.861f,
            0.639f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.195f,
            0.548f,
            0.859f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.014f,
            0.184f,
            0.576f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            1.0f,
            0.771f,
            0.328f,
            0.970f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            -1.0f,
            0.406f,
            0.615f,
            0.116f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            1.0f,
            0.676f,
            0.977f,
            0.133f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            1.0f,
            0.971f,
            0.572f,
            0.833f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            -1.0f,
            0.140f,
            0.616f,
            0.489f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            1.0f,
            0.997f,
            0.513f,
            0.064f,
        },
        atom::Vertex{
            -1.0f,
            -1.0f,
            1.0f,
            0.945f,
            0.719f,
            0.592f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            1.0f,
            0.543f,
            0.021f,
            0.978f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            1.0f,
            0.279f,
            0.317f,
            0.505f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            -1.0f,
            0.167f,
            0.620f,
            0.077f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            -1.0f,
            0.347f,
            0.857f,
            0.137f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            -1.0f,
            0.055f,
            0.953f,
            0.042f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            1.0f,
            0.714f,
            0.505f,
            0.345f,
        },
        atom::Vertex{
            1.0f,
            -1.0f,
            1.0f,
            0.783f,
            0.290f,
            0.734f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            1.0f,
            0.722f,
            0.645f,
            0.174f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            -1.0f,
            0.302f,
            0.455f,
            0.848f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            -1.0f,
            0.225f,
            0.587f,
            0.040f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            1.0f,
            0.517f,
            0.713f,
            0.338f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            -1.0f,
            0.053f,
            0.959f,
            0.120f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            1.0f,
            0.393f,
            0.621f,
            0.362f,
        },
        atom::Vertex{
            1.0f,
            1.0f,
            1.0f,
            0.673f,
            0.211f,
            0.457f,
        },
        atom::Vertex{
            -1.0f,
            1.0f,
            1.0f,
            0.820f,
            0.883f,
            0.371f,
        },
        atom::Vertex{1.0f, -1.0f, 1.0f, 0.982f, 0.099f, 0.879f},
    };

    */

    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    bool res = loadOBJ("shaders/tavsikucgen.obj", _vertices, uvs, normals);
    if (res)
    {
        std::cout << "Loaded" << std::endl;
    }

    std::vector<atom::Vertex> vertices;

    for (glm::vec3 v : _vertices)
    {
        vertices.push_back(atom::Vertex(v, random_vec3()));
    }

    std::cout << "vertices count " << vertices.size() << std::endl;

    atom::Model model(shader, vertices);
    models.push_back(model);
    models.push_back(model);
}

void atom::Engine::loop()
{
    GLuint MatrixID = glGetUniformLocation(shader, "MVP");
    Projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    // glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    glm::vec3 camPos = glm::vec3(4, 3, 3);
    glm::vec3 camTarget = glm::vec3(0);
    glm::vec3 camUp = glm::vec3(0, 1, 0);

    // Camera matrix
    View = glm::lookAt(
        camPos,    // Camera is at (4,3,3), in World Space
        camTarget, // and looks at the origin
        camUp      // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    Model = glm::mat4(1.0f);
    // Model = glm::rotate(Model, (float)M_PI / 2.f, glm::vec3(0.f, -1.f, 0.f));
    // Model = glm::translate(Model, glm::vec3(0.f, -.5, 0.f));
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP;

    glm::vec3 modelPos = glm::vec3(0.f);
    glm::vec3 modelRot = glm::vec3(0.f, -90.f, 0.f);

    do
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Text("Model");
        ImGui::InputFloat3("Pos", glm::value_ptr(modelPos));
        ImGui::InputFloat3("Rotation", glm::value_ptr(modelRot));

        Model = glm::rotate(glm::mat4(1.0f), glm::radians(modelRot.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(modelRot.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(modelRot.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
                glm::mat4(1.f);
        Model = glm::translate(glm::mat4(1.f), modelPos) * Model;

        // Model = glm::rotate(Model, (float)sin(glfwGetTime()) / 120.f, glm::vec3(.1f, 0.f, 0.f));
        // Model = glm::rotate(glm::mat4(1.f), (float)sin(glfwGetTime()), glm::vec3(0.1f, 0.f, 0.f));

        MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(shader);

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        for (atom::Model model : models)
        {
            model.draw();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
}

atom::Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
};