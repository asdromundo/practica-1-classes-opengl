#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "engine/Shader.hpp"
#include "engine/Mesh.hpp"

// Vertex Shader source code (GLSL 4.10)
const char *vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 vertexColor;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        vertexColor = aColor ;
    }
)";

// Fragment Shader source code (GLSL 4.10)
const char *fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    in vec3 vertexColor;

    void main()
    {
        //FragColor = vec4(vec3(1.0,0.0,0.0), 1.0);
        FragColor = vec4(vertexColor, 1.0);
    }
)";

int main()
{
    Window window(800, 600, "OpenGL Triangle");
    if (!window.native())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window.native());

    Renderer renderer;
    if (!renderer.init(window.native()))
    {
        std::cerr << "Failed to init renderer" << std::endl;
        return 1;
    }

    Shader shader;
    if (!shader.loadFromSource(vertexShaderSource, fragmentShaderSource))
    {
        std::cerr << "Shader compile/link failed:\n"
                  << shader.log() << std::endl;
        return 1;
    }

    // Set up vertex data and buffers and configure vertex attributes
    /*float vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f
    };*/

    // 6 vertices (2 triangles)
    float vertices[] = {
        -1.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        1.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f};

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f};

    Mesh mesh;
    mesh.setup(vertices, colors, 6);

    // Render loop
    while (window.isOpen())
    {
        window.pollEvents();

        // input
        if (glfwGetKey(window.native(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.close();

        renderer.clear();
        renderer.setClearColor(0.0f, 0.3f, 0.8f, 1.0f);
        renderer.draw(mesh, shader);

        window.swapBuffers();
    }

    return 0;
}