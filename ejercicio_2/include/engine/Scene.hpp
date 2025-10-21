#include <vector>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include <iostream>
#include <memory>

class Scene
{
public:
    Scene(Shader *s) : shader(s) {}

    void addMesh(const float *vertices, const float *colors, size_t vertexCount)
    {
        auto m = std::make_unique<Mesh>();
        m->setup(vertices, colors, vertexCount);
        meshes.push_back(std::move(m));
    }

    virtual void render(Renderer &renderer)
    {
        // shader->use();
        for (auto &mesh : meshes)
        {
            renderer.draw(*mesh, *shader);
        }
    }
    Shader *shader; // common shader

    std::vector<std::unique_ptr<Mesh>> meshes;

protected:
};
