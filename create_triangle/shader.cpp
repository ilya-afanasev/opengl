//
// Created by mamba on 13.06.17.
//

#include "shader.h"

ShaderProgramWrapper::ShaderProgramWrapper(const GLchar* vertex_path, const GLchar* fragment_path) : shader_program(0)
{
    std::string vertex_code = read_file(vertex_path);
    std::string fragment_code = read_file(fragment_path);

    GLuint vertex_shader = build_shader(vertex_code, GL_VERTEX_SHADER);
    GLuint fragment_shader = build_shader(fragment_code, GL_FRAGMENT_SHADER);

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    GLint success = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[512] = {};
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        throw std::runtime_error(info);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderProgramWrapper::use()
{
    glUseProgram(shader_program);
}

std::string ShaderProgramWrapper::read_file(const GLchar* file_path)
{
    std::stringstream code;
    std::ifstream file(file_path);
    if (!file)
    {
        return "";
    }
    std::string line;
    while (std::getline(file, line))
    {
        code << line << std::endl;
    }
    return code.str();
}

GLuint ShaderProgramWrapper::build_shader(const std::string& code, GLuint type)
{
    GLuint shader_id = glCreateShader(type);
    const GLchar* shader_c_str = code.c_str();

    glShaderSource(shader_id, 1, &shader_c_str, NULL);
    glCompileShader(shader_id);

    GLint success = 0;
    GLchar info_log[512] = {};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        throw std::runtime_error(info_log);
    }
    return shader_id;
}