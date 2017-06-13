#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <cmath>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLfloat vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};
GLuint indices[] = {
        0, 1, 2,
};

const GLuint WIDTH = 800, HEIGHT = 600;

const char* const vertex_shader = "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec4 color;\n"
        "out vec4 vertex_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "    vertex_color = color;"
        "}";

const char* const fragment_shader = "#version 330 core\n"
        "\n"
        "in vec4 vertex_color;\n"
        "out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    color = vertex_color;\n"
        "}";


GLuint build_shader(const char* shader, GLuint type)
{
    GLuint shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &shader, NULL);
    glCompileShader(shader_id);

    GLint success = 0;
    GLchar info_log[512] = {};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        std::stringstream ss;
        ss << "ERROR::SHADER::COMPILATION_FAILED" << std::endl << info_log << std::endl;
        throw std::runtime_error(ss.str());
    }
    return shader_id;
}

int main()
{
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint vertex_shader_id = build_shader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fragment_shader_id = build_shader(fragment_shader, GL_FRAGMENT_SHADER);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_id);
    glAttachShader(shader_program, fragment_shader_id);
    glLinkProgram(shader_program);

    GLint success = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[512] = {};
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        std::cerr << info << std::endl;
    }
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint ebo = 0;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        GLdouble current_time = glfwGetTime();
//        GLfloat green = static_cast<GLfloat>((sin(current_time) / 2) + 0.5);
//        GLint vertex_color = glGetUniformLocation(shader_program, "vertex_color");
        glUseProgram(shader_program);
//        glUniform4f(vertex_color, 0.0f, green, 0.0f, 1.0f);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
