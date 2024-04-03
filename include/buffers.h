#include "../thirdparty/glad/include/glad/glad.h"

struct VBO
{
    unsigned int ID;

    VBO(float* vertices, unsigned int size);
    void Bind();
    void Unbind();
    void Clear();
};

struct EBO
{
    unsigned int ID;

    EBO(unsigned int* indices, unsigned int size);
    void Bind();
    void Unbind();
    void Clear();
};

struct VAO
{
    unsigned int ID;

    VAO();
    void LinkVBO(VBO& VBO, unsigned int layout, GLsizei stride, void* offset); // stride = length between start of one vertex info and the start of next | offset = starting pos
    void Bind();
    void Unbind();
    void Clear();
    
};

    /*
    // Create vertex array object (VAO)
    // VAO's will store Enable/Disable VertexAttribArrayEnable calls, vertex attribute configs via glVertexAttribPointer, and VBO's with associated with vertex attributes
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Bind VAO as the current state to be used
    glBindVertexArray(VAO);

    // Create the vertex buffer object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // State-setting function tells GLAD to use the VBO object as the current state for GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Input Data into the VBO | STATIC - data is set only once, used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Describe how the vertex data in the binded VBO should be read
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create the element buffer object (EBO)
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // Bind EBO as the current state for GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind VBO as the current state of the GL_ARRAY_BUFFER
    // VBO is already stored in VAO via the glVertexAttribPointer call while the VBO was binded
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO to avoid accidental modification
    glBindVertexArray(0);
    // ONLY AFTER THE VAO IS UNBINDED CAN WE UNBIND ITS ASSOCIATED ELEMENT ARRAY BUFFER OBJECT (EBO)
    // The most recently binded EBO while a VAO is bound is stored in the binded VAO
    // Therefore, binding to that VAO will also automatically bind that EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    */