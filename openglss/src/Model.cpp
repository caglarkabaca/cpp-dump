#include "Model.h"

#include "utils.h"

#include <iostream>
#include <cstdio>
#include <exception>
#include <stdexcept>

#include "glm/gtx/string_cast.hpp"

atom::Model::Model(atom::Shader _shader, std::vector<atom::Vertex> buffer) : shader(_shader)
{
    if (!shader.isComplied)
        shader.compile();

    std::cout << "shader program id: " << shader.getProgram() << std::endl;

    MVP = glGetUniformLocation(shader.getProgram(), "MVP");

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    vertex_count = buffer.size();
    std::cout << "vertex count: " << vertex_count << std::endl;
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(atom::Vertex), &buffer[0], GL_STATIC_DRAW);
    vertices = buffer;
}

void atom::Model::draw(glm::mat4 &projection, glm::mat4 &view)
{

    mvp = projection * view * ModelMatrix;

    glUseProgram(shader.getProgram());
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glVertexAttribPointer(
        0,                 // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                 // size
        GL_FLOAT,          // type
        GL_FALSE,          // normalized?
        6 * sizeof(float), // stride
        (void *)0          // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,                          // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                          // size
        GL_FLOAT,                   // type
        GL_FALSE,                   // normalized?
        6 * sizeof(float),          // stride
        (void *)(3 * sizeof(float)) // array buffer offset
    );
    glEnableVertexAttribArray(1);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertex_count); // 3 indices starting at 0 -> 1 triangle
}

void atom::Model::updatePosition()
{
    glm::mat4 Model = glm::rotate(glm::mat4(1.0f), glm::radians(modelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                      glm::rotate(glm::mat4(1.0f), glm::radians(modelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                      glm::rotate(glm::mat4(1.0f), glm::radians(modelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
                      glm::mat4(1.f);
    Model = glm::translate(glm::mat4(1.f), modelPosition) * Model;
    ModelMatrix = glm::mat4(Model);
}

// #########################################################################################

std::vector<atom::Vertex> atom::ObjModel::getBuffer(char *objPath)
{
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    bool res = loadOBJ(objPath, _vertices, uvs, normals);
    if (res)
        std::cout << "Loaded count: " << _vertices.size() << std::endl;

    std::vector<atom::Vertex> vertices;
    for (glm::vec3 v : _vertices)
    {
        vertices.push_back(atom::Vertex(v, random_vec3()));
    }

    return vertices;
}

atom::ObjModel::ObjModel(atom::Shader _shader, char *objPath) : Model(_shader, getBuffer(objPath))
{
    obj = objPath;
}

void atom::ObjModel::serialize(int id, char *buffer)
{
    snprintf(buffer, 1024, "%d&%s&%s&%s", id, obj, shader.vertexShaderPath, shader.fragmentShaderPath);
}