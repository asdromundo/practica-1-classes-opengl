#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "scenes/MainScene.hpp"

int main()
{
    Window window(800, 600, "OpenGL Triangle");

    Renderer renderer;
    if (!renderer.init(window.native()))
    {
        std::cerr << "Failed to init renderer" << std::endl;
        return 1;
    }

    Scene *scene = new MainScene();

    // Render loop
    while (window.isOpen())
    {
        window.pollEvents();

        // input
        if (glfwGetKey(window.native(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.close();
        scene->render(renderer);

        window.swapBuffers();
    }

    return 0;
}