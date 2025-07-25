#define GLEW_STATIC
#include "include/glew.h"
#include "include/glfw3.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

std::string GetShader(std::string &filepath)
{

    std::ifstream f(filepath);
    std::string line;
    std::stringstream s;
    
    while(std::getline(f, line))
    {
        s << line << "\n";
    }

    std::cout << s.str() << "\n";

    return s.str();

}

unsigned int CreateShaders(std::string &vsSource, std::string &fsSource)
{

    unsigned int vertex, fragment, program;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vsrc = vsSource.c_str();
    const char *fsrc = fsSource.c_str();

    glShaderSource(vertex, 1, &vsrc, nullptr);
    glShaderSource(fragment, 1, &fsrc, nullptr);

    glCompileShader(vertex);
    glCompileShader(fragment);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;

}

int main()
{

    GLFWwindow *window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "Spinning Cube", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };


    unsigned int buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    std::string vsFile = "shaders/vertex.shader";
    std::string fsFile = "shaders/fragment.shader";

    std::string vs = GetShader(vsFile);
    std::string fs = GetShader(fsFile);

    unsigned int program = CreateShaders(vs, fs);
    glUseProgram(program);

    glm::mat4 trans = glm::mat4(1.0f);

    float currTime = glfwGetTime();
    float lastTime = currTime;
    float deltaTime;

    while(!glfwWindowShouldClose(window))
    {

        currTime = glfwGetTime();
        deltaTime = currTime - lastTime;
        lastTime = currTime;

        glClear(GL_COLOR_BUFFER_BIT);

        trans = glm::rotate(trans, deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));

        unsigned int id = glGetUniformLocation(program, "u_Trans");
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(trans));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}