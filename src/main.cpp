// IMPORTANT GAME DEV LIBRARIES (Graphics, sounds, textures, etc.)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include "../thirdparty/imgui-docking/imgui\backends/imgui_impl_glfw.h"
#include "../thirdparty/imgui-docking/imgui\backends/imgui_impl_opengl3.h"
#include <raudio.h>
#include <stb_image/stb_image.h>
#include <stb_truetype/stb_truetype.h>

// Standard Libraries

#include <iostream>
#include <fstream>

// My Libraries

#include <buffers.h>
#include <shaderProgram.h>
#include <interface.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void checkKeyInputs(GLFWwindow* window);
std::string readFileContents(const char* filename, bool debug);
void initMenu(const char* windowName);
void closeMenu();

int main()
{
    // INITIALIZATION

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

    // Initialize imgui and attach associated io object
    ImGuiIO& io = initializeImGUI(window);

    // GRAPHICS
    float vertices[] = {
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // top right 0
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom right 1 
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left 2
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // top left 3
    };
    unsigned int indices[] = {  // note that we start from 0!
        3, 0, 2,   // first triangle
        2, 0, 1    // second triangle
    };

    ShaderProgram custom("default.vert", "default.frag", false);
    ShaderProgram custom2("default.vert", "yellow.frag", false);

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, 24);

    EBO EBO1(indices, 6);

    VAO1.LinkVBO(VBO1, 0, 6 * sizeof(float), (void*)0);
    VAO1.LinkVBO(VBO1, 1, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    // Configure how OpenGL draws primatives (1st Arg: Apply to both front and back | 2nd Arg: How to draw them)
    // Any subsequent draw calls will use this configuration until glPolygonMode is configured again
    // Good for debugging since it draws wireframes
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glm::mat4 translationMatrix = glm::mat4(1.0f); // 4x4 Identity Matrix to start
    glm::vec3 scaleVector = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 translationVector = glm::vec3(0.0f, 0.0f, 0.0f);
  
    float scale = 1.0f;

    // render loop (frame)
    while (!glfwWindowShouldClose(window))
    {
        
        // HANDLE EVENTS
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("DEBUG");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("float", &scale, 0.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // Input processing
        checkKeyInputs(window);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            translationVector.x += -0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            translationVector.x += 0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            translationVector.y += 0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            translationVector.y += -0.01f;
        }

        translationMatrix = glm::mat4(1.0f);
        translationMatrix = glm::scale(translationMatrix, glm::vec3(scale, scale, scale));
        translationMatrix = glm::translate(translationMatrix, translationVector);
        

        // Specify background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean back buffer and assign new color
        glClear(GL_COLOR_BUFFER_BIT);

        // RENDER
        
        VAO1.Bind();

        // Update shaderProgram custom's fragment shader via uniform
        // float time = glfwGetTime();
        // float colorValue = sin(time) / 2.0f + 0.5f;
        // int fragUniformLocation = glGetUniformLocation(custom.ID, "ourColor");
        // glUniform4f(fragUniformLocation, 0.0f, colorValue, 0.0f, 1.0f);
        
        custom2.UseProgram();

        int vertexUniformLocation = glGetUniformLocation(custom2.ID, "translate");
        glUniformMatrix4fv(vertexUniformLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0); // First 3 indices
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int))); // Last 3 indices (offset is the size of 3 unsigned ints, skips first 3 indices)

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    // Terminate imgui
    terminateImGUI();



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