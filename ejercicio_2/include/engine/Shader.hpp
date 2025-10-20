#pragma once
#include <string>
// #include <GL/gl.h>

class Shader
{
public:
    Shader();
    ~Shader();

    bool loadFromSource(const std::string &vertexSrc, const std::string &fragmentSrc);
    void use() const;
    unsigned int id() const { return m_id; }
    bool isValid() const { return m_valid; }
    const std::string &log() const { return m_log; }

private:
    unsigned int m_id = 0;
    bool m_valid = false;
    std::string m_log;
};
