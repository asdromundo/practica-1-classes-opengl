#pragma once
#include <cstddef>

class Shader;
class Mesh;

class Renderer
{
public:
    Renderer() = default;
    ~Renderer() = default;

    bool init(void *_glfwWindowPtr);
    void setClearColor(float r, float g, float b, float a);
    void clear();
    void draw(const Mesh &mesh, const Shader &shader);
    void viewport(int w, int h);
};
