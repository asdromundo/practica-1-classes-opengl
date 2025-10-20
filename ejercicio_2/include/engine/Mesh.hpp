#pragma once
#include <cstddef>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // Non-interleaved buffers: positions (3 floats per vert) and colors (3 floats per vert)
    bool setup(const float *positions, const float *colors, size_t vertexCount);
    void draw() const;
    size_t vertexCount() const { return m_vertexCount; }

private:
    unsigned int m_vao = 0;
    unsigned int m_vboPos = 0;
    unsigned int m_vboColor = 0;
    size_t m_vertexCount = 0;
};
