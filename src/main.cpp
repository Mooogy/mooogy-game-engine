// IMPORTANT GAME DEV LIBRARIES (Graphics, sounds, textures, etc.)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <raudio.h>
#include <stb_image/stb_image.h>
#include <stb_truetype/stb_truetype.h>

// Standard Libraries

#include <iostream>
#include <fstream>

// My Libraries

#include <buffers.h>
#include <shaderProgram.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void checkKeyInputs(GLFWwindow* window);
std::string readFileContents(const char* filename, bool debug);

int main()
{
    // Initialize GLFW
    glfwInit();

    // Specify to GLFW what version of OpenGL to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // Specify what profile GLFW uses (CORE = Modern Functions)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(800, 800, "Simulation", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Error check window has been created successfully
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD to configure openGL
    gladLoadGL();

    // Error check if GLAD was initialized successfully
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   


    // Specify viewport of OpenGL in the window (From 0,0 to 800,800)
    glViewport(0, 0, 800, 800);

    // GRAPHICS
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    ShaderProgram orange("default.vert", "default.frag", false);
    ShaderProgram yellow("default.vert", "yellow.frag", false);

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));

    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    // Configure how OpenGL draws primatives (1st Arg: Apply to both front and back | 2nd Arg: How to draw them)
    // Any subsequent draw calls will use this configuration until glPolygonMode is configured again
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     

    // render loop (frame)
    while (!glfwWindowShouldClose(window))
    {
        
        // Input processing
        checkKeyInputs(window);

        // Specify background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean back buffer and assign new color
        glClear(GL_COLOR_BUFFER_BIT);

        // RENDER
        
        VAO1.Bind();
        orange.UseProgram();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // First 3 indices
        yellow.UseProgram();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int))); // Last 3 indices (offset is the size of 3 unsigned ints, skips first 3 indices)


        // HANDLE EVENTS
        glfwPollEvents();
        // Swap front and back buffer
        glfwSwapBuffers(window);
    }

    // Close the window
    glfwDestroyWindow(window);

    // Optional: De-allocate resources after they are no longer needed
    VAO1.Clear();
    VBO1.Clear();
    EBO1.Clear();

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

void checkKeyInputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
