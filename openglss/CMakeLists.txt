cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)

project(openglss LANGUAGES CXX)

find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(header)
include_directories(imgui)
include_directories(imgui/backends)
file(COPY ./shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES src/*.cpp imgui/*.cpp imgui/backends/*.cpp)
add_executable(server server.cpp ${SOURCES})
set_property(TARGET server PROPERTY CXX_STANDARD 11)
target_link_libraries(server GLEW::GLEW glfw glm::glm OpenGL::GL)

add_executable(client client.cpp ${SOURCES})
set_property(TARGET client PROPERTY CXX_STANDARD 11)
target_link_libraries(client GLEW::GLEW glfw glm::glm OpenGL::GL)