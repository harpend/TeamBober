#include "imgui.h"
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <print>

#include "src/user_interface.h"
#include "src/bb_images.h"

#include <filesystem>

renderer bobr_ui;

int main()
{
  GLFWwindow* window;
  if (!glfwInit())
  {
    return -1;
  }

  window = glfwCreateWindow(1280, 820, "bobr", nullptr, nullptr);

  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    std::print("noo!!");
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");
  
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImFont* f = io.Fonts->AddFontFromFileTTF("assets/jetbrains.ttf", 30);


  
  ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;

  
  ImGui::GetStyle().ScaleAllSizes(1.75);
  // ImGui::GetIO().FontGlobalScale = 1.25;

  bobr_ui.init();
  
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    bobr_ui.draw_ui();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  bobr_ui.shutdown();

  glfwTerminate();
  
}
