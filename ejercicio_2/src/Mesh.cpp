#include "engine/Mesh.hpp"
#include <GL/glew.h>
#include <cstring>

Mesh::Mesh() {}
Mesh::~Mesh()
{
    if (m_vboColor)
        glDeleteBuffers(1, &m_vboColor);
    if (m_vboPos)
        glDeleteBuffers(1, &m_vboPos);
    if (m_vao)
        glDeleteVertexArrays(1, &m_vao);
}

bool Mesh::setup(const float *positions, const float *colors, size_t vertexCount)
{
    m_vertexCount = vertexCount;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vboPos);
    glGenBuffers(1, &m_vboColor);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboColor);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return true;
}

void Mesh::draw() const
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertexCount);
    glBindVertexArray(0);
}
