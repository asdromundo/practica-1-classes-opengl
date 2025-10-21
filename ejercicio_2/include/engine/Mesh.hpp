#pragma once
#include <cstddef>
#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    // Non-interleaved buffers: positions (3 floats per vert) and colors (3 floats per vert)
    bool setup(const float *positions, const float *colors, size_t vertexCount);
    void draw() const;
    size_t vertexCount() const { return m_vertexCount; }
    GLenum drawMode() const { return m_drawMode; }
    void setDrawMode(GLenum mode) { m_drawMode = mode; }

private:
    unsigned int m_vao = 0;
    unsigned int m_vboPos = 0;
    unsigned int m_vboColor = 0;
    size_t m_vertexCount = 0;
    GLenum m_drawMode = GL_TRIANGLES;
};
