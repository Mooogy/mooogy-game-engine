#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// THIRD-PARTY LIBS
#include "../thirdparty/glad/include/glad/glad.h" // Interacting with OpenGL

// STANDARD LIBS
#include <iostream> // Outputting debug information
#include <fstream> // Reading from files

std::string readFileContents(const char* filename, bool debug);

struct ShaderProgram
{
    unsigned int ID; // Where the ShaderProgram is stored

    // Constructor that takes in vert and frag file names (FILES MUST BE IN RESOURCES FOLDER) | Has toggle to show debug information
    ShaderProgram(const char* vertexShaderFile, const char* fragShaderFile, bool debug);

    // Tells OpenGL to use this program as the current state
    void UseProgram(); 
};

#endif