#version 330 core
in vec3 col;
out vec4 fColor;

void main()
{
    fColor = vec4(col, 1.0f);
}