#ifndef INTERFACE_H
#define INTERFACE_H

#include <imgui.h>
#include "../thirdparty/imgui-docking/imgui\backends/imgui_impl_glfw.h"
#include "../thirdparty/imgui-docking/imgui\backends/imgui_impl_opengl3.h"

ImGuiIO& initializeImGUI(GLFWwindow* window);

void terminateImGUI();

#endif