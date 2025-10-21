#pragma once

#include "engine/Scene.hpp"
#include "engine/Shader.hpp"

class MainScene : public Scene
{
public:
    MainScene();
    void render(Renderer &renderer) override;

private:
    Shader m_shader;
};
