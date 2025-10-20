#include "engine/Renderer.hpp"
#include "engine/Shader.hpp"
#include "engine/Mesh.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool Renderer::init(void *glfwWindowPtr)
{
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // glEnable(GL_DEPTH_TEST);
    return true;
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Mesh &mesh, const Shader &shader)
{
    shader.use();
    mesh.draw();
}

void Renderer::viewport(int w, int h)
{
    glViewport(0, 0, w, h);
}
