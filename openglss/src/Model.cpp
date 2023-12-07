#include "Model.h"

#include <cstdio>
#include <exception>
#include <stdexcept>

atom::Model::Model(GLuint shader, std::vector<atom::Vertex> buffer)
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    assigned_shader = shader;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    vertex_count = buffer.size();
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(atom::Vertex), &buffer[0], GL_STATIC_DRAW);
}

void atom::Model::draw()
{
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