#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#define random_vec3() glm::vec3(std::rand() / static_cast<float>(RAND_MAX), std::rand() / static_cast<float>(RAND_MAX), std::rand() / static_cast<float>(RAND_MAX))
GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
bool loadOBJ(
    const char *path,
    std::vector<glm::vec3> &out_vertices,
    std::vector<glm::vec2> &out_uvs,
    std::vector<glm::vec3> &out_normals);
    
#endif