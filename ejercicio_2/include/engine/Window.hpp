#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window
{
public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool isOpen() const;
    void pollEvents();
    void swapBuffers();
    void close();

    GLFWwindow *native() const { return m_window; }

private:
    GLFWwindow *m_window = nullptr;
    int m_width = 0, m_height = 0;
};
