#include "engine/Shader.hpp"
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static std::string getShaderLog(unsigned int obj)
{
    int len = 0;
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &len);
    if (len <= 1)
        return "";
    std::vector<char> buf(len);
    glGetShaderInfoLog(obj, len, nullptr, buf.data());
    return std::string(buf.data());
}

static std::string getProgramLog(unsigned int prog)
{
    int len = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len <= 1)
        return "";
    std::vector<char> buf(len);
    glGetProgramInfoLog(prog, len, nullptr, buf.data());
    return std::string(buf.data());
}

Shader::Shader() {}
Shader::~Shader()
{
    if (m_id)
        glDeleteProgram(m_id);
}

bool Shader::loadFromSource(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vsrc = vertexSrc.c_str();
    glShaderSource(vs, 1, &vsrc, nullptr);
    glCompileShader(vs);
    std::string vlog = getShaderLog(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fsrc = fragmentSrc.c_str();
    glShaderSource(fs, 1, &fsrc, nullptr);
    glCompileShader(fs);
    std::string flog = getShaderLog(fs);

    m_id = glCreateProgram();
    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);

    std::string plog = getProgramLog(m_id);

    // cleanup
    glDeleteShader(vs);
    glDeleteShader(fs);

    m_log = vlog + "\n" + flog + "\n" + plog;
    GLint status = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    m_valid = (status == GL_TRUE);
    return m_valid;
}

void Shader::use() const
{
    if (m_valid)
        glUseProgram(m_id);
}
