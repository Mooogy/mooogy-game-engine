#include "../include/buffers.h"

// VBO FUNCTIONALITY

VBO::VBO(float* vertices, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    // Determine buffer data parameter size

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
}
void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Clear()
{
    glDeleteBuffers(1, &ID);
}



// EBO FUNCTIONALITY

EBO::EBO(unsigned int* indices, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}
void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Clear()
{
    glDeleteBuffers(1, &ID);
}


// VAO FUNCTIONALITY

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}
void VAO::LinkVBO(VBO& VBO, unsigned int layout, GLsizei stride, void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}
void VAO::Bind()
{
    glBindVertexArray(ID);
}
void VAO::Unbind()
{
    glBindVertexArray(0);
}
void VAO::Clear()
{
    glDeleteVertexArrays(1, &ID);
}