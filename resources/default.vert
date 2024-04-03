#version 460 core
layout (location = 0) in vec3 aPos; // the position variable has attribute location 0
layout (location = 1) in vec3 aColor; // the position variable has attribute location 1

out vec3 vertexColor; // specify color output to fragment shader

uniform mat4 translate;

void main()
{
    gl_Position = translate * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
}
