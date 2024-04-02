#ifndef CUBE_H
#define CUBE_H

// STANDARD LIBS
#include <iostream>

// THIRD PARTY LIBS
#include "../thirdparty/glad/include/glad/glad.h"

// MY LIBS
#include "buffers.h"


struct Cube
{
    // Cubes will always have 8 vertices
    float vertices[8];
    // VBO to store all the cubes vertex information (will be binded to a VAO using VAO.LinkVBO method)
    VBO cubeVBO;

    //Cube(float xPos, float yPos, float zPos); // Given an x, y, z for the top left vertex, calculate rest of vertices 
};




#endif