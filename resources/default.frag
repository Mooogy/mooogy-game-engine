#version 460 core
out vec4 FragColor;

uniform vec4 ourColor; // we set uniform value in OpenGL code

void main()
{
    FragColor = ourColor;
}
