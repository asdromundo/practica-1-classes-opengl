#include "engine/Window.hpp"
#include <stdexcept>
#include <iostream>

Window::Window(int width, int height, const std::string &title)
    : m_width(width), m_height(height)
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
}

Window::~Window()
{
    if (m_window)
        glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::isOpen() const { return m_window && !glfwWindowShouldClose(m_window); }
void Window::pollEvents()
{
    if (m_window)
        glfwPollEvents();
}
void Window::swapBuffers()
{
    if (m_window)
        glfwSwapBuffers(m_window);
}
void Window::close()
{
    if (m_window)
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}
