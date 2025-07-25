#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aCol;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 col;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    col = aCol;
}