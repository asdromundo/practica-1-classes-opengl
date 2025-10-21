// Implementación de MainScene como clase que hereda de Scene
#include "scenes/MainScene.hpp"
#include "engine/Mesh.hpp"
#include <iostream>

MainScene::MainScene() : Scene(&m_shader)
{

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
        FragColor = vec4(vertexColor, 1.0);
    }
)";

    if (!m_shader.loadFromSource(vertexShaderSource, fragmentShaderSource))
    {
        std::cerr << "Shader compile/link failed:\n"
                  << m_shader.log() << std::endl;
    }

    // 6 vértices (2 triángulos)
    {
        float vertices[] = {
            -1.0f, 1.0f, 0.0f,
            -0.7f, 1.0f, 0.0f,
            -1.0f, 0.7f, 0.0f,

            -1.0f, 0.7f, 0.0f,
            -0.7f, 1.0f, 0.0f,
            -0.7f, 0.7f, 0.0f};

        float colors[] = {
            0.5, 0.5f, 0,
            0.5, 0.5f, 0,
            0.5, 0.5f, 0,
            0.5, 0.5f, 0,
            0.5, 0.5f, 0,
            0.5, 0.5f, 0};

        addMesh(vertices, colors, 6);
    }

    // Triángulo simple
    {
        float positions[] = {
            1.0f, 1.0f, 0.0f,
            0.5f, 1.0f, 0.0f,
            1.0f, 0.5f, 0.0f};

        float colors2[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f};

        addMesh(positions, colors2, 3);
    }

    // Triangulo central
    {
        float vertices[] = {
            -0.3f, -0.3f, 0.0f,
            0.3f, -0.3f, 0.0f,
            0.0f, 0.3f, 0.0f};

        float colors[] = {
            1.0f, 0.0f, 0.0f, // rojo
            0.0f, 1.0f, 0.0f, // verde
            0.0f, 0.0f, 1.0f  // azul
        };
        addMesh(vertices, colors, 3);
    }

    // Cuadrado
    {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,

            -0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};

        float colors[] = {
            0.5, 0, 0,
            0.5, 0, 0,
            0.5, 0, 0,
            0.5, 0, 0,
            0.5, 0, 0,
            0.5, 0, 0};

        addMesh(vertices, colors, 6);
    }

    // Rombo
    {
        float vertices[] = {
            // triángulo 1: top, left, right
            -0.85f, -0.68f, 0.0f, // top
            -0.97f, -0.80f, 0.0f, // left
            -0.73f, -0.80f, 0.0f, // right

            // triángulo 2: bottom, right, left
            -0.85f, -0.92f, 0.0f, // bottom
            -0.73f, -0.80f, 0.0f, // right
            -0.97f, -0.80f, 0.0f  // left
        };

        float colors[] = {
            0.8f, 0.5f, 0.5f,
            0.8f, 0.5f, 0.5f,
            0.8f, 0.5f, 0.5f,
            0.8f, 0.5f, 0.5f,
            0.8f, 0.5f, 0.5f,
            0.8f, 0.5f, 0.5f};
        addMesh(vertices, colors, 6);
    }

    // Pentagono
    {
        float vertices[] = {
            // tri 1 (p0, p1, p2)
            0.85f, -0.73f, 0.0f,
            0.964f, -0.813f, 0.0f,
            0.9205f, -0.9471f, 0.0f,

            // tri 2 (p0, p2, p3)
            0.85f, -0.73f, 0.0f,
            0.9205f, -0.9471f, 0.0f,
            0.7795f, -0.9471f, 0.0f,

            // tri 3 (p0, p3, p4)
            0.85f, -0.73f, 0.0f,
            0.7795f, -0.9471f, 0.0f,
            0.736f, -0.8129f, 0.0f};

        float colors[] = {
            1.0f, 0.6f, 0.0f, // tri1 v0
            1.0f, 0.6f, 0.0f, // tri1 v1
            1.0f, 0.6f, 0.0f, // tri1 v2

            1.0f, 0.6f, 0.0f, // tri2 v0
            1.0f, 0.6f, 0.0f, // tri2 v1
            1.0f, 0.6f, 0.0f, // tri2 v2

            1.0f, 0.6f, 0.0f, // tri3 v0
            1.0f, 0.6f, 0.0f, // tri3 v1
            1.0f, 0.6f, 0.0f  // tri3 v2
        };

        addMesh(vertices, colors, 9);
    }
}

void MainScene::render(Renderer &renderer)
{
    renderer.clear();
    renderer.setClearColor(0.0f, 0.3f, 0.8f, 1.0f);
    Scene::render(renderer);
}