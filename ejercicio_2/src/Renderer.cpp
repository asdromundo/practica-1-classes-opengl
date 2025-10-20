#include "engine/Renderer.hpp"
#include "engine/Shader.hpp"
#include "engine/Mesh.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool Renderer::init(void *glfwWindowPtr)
{
    // glfwWindowPtr is not used here, but keep for future use
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Renderer: Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
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
