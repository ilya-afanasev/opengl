#ifndef CREATE_TRIANGLE_SHADER_H
#define CREATE_TRIANGLE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

struct ShaderProgramWrapper
{
    GLuint shader_program;

    ShaderProgramWrapper(const GLchar* vertex_path, const GLchar* fragment_path);
    void use();

private:
    std::string read_file(const GLchar* file_path);
    GLuint build_shader(const std::string& code, GLuint type);
};

#endif //CREATE_TRIANGLE_SHADER_H
