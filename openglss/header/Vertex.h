#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace atom
{
    struct Vertex
    {
        float x, y, z;
        float r, g, b;

        Vertex(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z), r(r), g(g), b(b) {}

        Vertex(const glm::vec3 &xyz, const glm::vec3 &rgb) : x(xyz.x), y(xyz.y), z(xyz.z), r(rgb.r), g(rgb.g), b(rgb.b) {}
    };
}

#endif