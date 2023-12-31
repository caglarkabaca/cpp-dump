#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

uniform mat4 MVP;

void main(){

    gl_Position = MVP * vec4(pos, 1.0);
    fragmentColor = vertexColor;
}