#include "../include/shaderProgram.h"

std::string readFileContents(const char* filename, bool debug)
{
    std::ifstream inFile(filename, std::ios_base::binary);

    // Error check if file was found
    if (!inFile)
    {
        std::cout << filename << " was not found!" << std::endl;
        throw(errno);
    }

    std::string contents;

    // Set read position to the last position
    inFile.seekg(0, std::ios_base::end);
    // Resize the string to match the size of all the chars in the file
    contents.resize(inFile.tellg());
    // Set read position to the beginning for reading from file
    inFile.seekg(0, std::ios_base::beg);
    // Read file contents into a string the size of the file's contents
    inFile.read(&contents[0], contents.size());

    // Close the file so it can be used properly by future filestreams
    inFile.close();

    if (debug) // Debugging mode on
    {
        std::cout << contents << std::endl;
    }

    return contents;
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragShaderFile, bool debug)
{
    int success; // DEBUGGING VARIABLE
    char infoLog[512]; // DEBUGGING VARIABLE

    std::string resourcesPath = RESOURCES_PATH;
    std::string vertexShaderFileName = resourcesPath + vertexShaderFile;
    std::string fragmentShaderFileName = resourcesPath + fragShaderFile;
    
    // COMPILE VERTEX SHADER

    // Create vertex shader object
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Import vertex shader source code from a file
    
    std::string vertexShaderFileContent = readFileContents(vertexShaderFileName.c_str(), debug);
    const char* vertexShaderSource = vertexShaderFileContent.c_str();

    // Next, attach shader source code and compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Error check if vertex shader was compiled correctly
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "VERTEX SHADER COMPILE ERROR: " << infoLog << std::endl;

        throw (errno);
    }

    // COMPILE FRAGMENT SHADER

    // Create the fragment shader object
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Import fragment shader source code from a file
    std::string fragmentShaderFileContent = readFileContents(fragmentShaderFileName.c_str(), debug);
    const char* fragmentShaderSource = fragmentShaderFileContent.c_str();

    // Attach fragment shader source code and compile
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Error check if fragment shader was compiled correctly
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "FRAGMENT SHADER COMPILE ERROR: " << infoLog << std::endl;

        throw (errno);
    }

    // CREATE PROGRAM AND LINK SHADERS

    // Create shader program that will hold our shaders
    ID = glCreateProgram();

    // Attach shaders to the current context
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    // Link attatched shaders to the program
    glLinkProgram(ID);

    // Error check if the shaders were linked properly
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "PROGRAM LINK ERROR:" << std::endl << infoLog << std::endl;

        throw (errno);
    }

    // DELETE ALREADY LINKED SHADERS
    // Can now delete the shader objects since the data has been linked to the shaderProgram already

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::UseProgram()
{
    glUseProgram(ID);
}