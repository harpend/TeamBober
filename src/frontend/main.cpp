#include "imgui.h"
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <print>


void draw_ui()
{

  
  static bool show_overdraw{ false }, show_ssao{ false }, show_collision{ false }, show_debug_lines{ false }, show_overlay{ true };

  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);

  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::Begin("Lucerna Engine", nullptr, window_flags);

  
  ImGui::DockSpace(ImGui::GetID("Lucerna Engine"), ImVec2{0.0f, 0.0f},  dockspace_flags);

  
  ImGui::PopStyleVar(3);


  ImGui::Begin("Feed");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();

  ImGui::Begin("Reports");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();
  
  ImGui::Begin("Saved Issues");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();
  
if (ImGui::BeginMenuBar())
  {
    ImGui::PushItemFlag(ImGuiItemFlags_AutoClosePopups, false);
    

    if (ImGui::BeginMenu("Account"))
    {
      ImGui::Text("settings and other stuff");
      
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Community"))
    {
      ImGui::Text("current:");
      ImGui::Text("join:");
      
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("About"))
    {
      ImGui::Text("bobr-app v0.1.0");
      ImGui::Text("by team-bober");
      ImGui::SameLine();
      ImGui::TextLinkOpenURL("(repo)", "https://github.com/harpend/TeamBober");
      
      ImGui::EndMenu();
    }
    
    ImGui::EndMenuBar();
    ImGui::PopItemFlag();
  }
  ImGui::End();
  
}

int main()
{
  GLFWwindow* window;
  if (!glfwInit())
  {
    return -1;
  }

  window = glfwCreateWindow(1280, 820, "bober-app", nullptr, nullptr);

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
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
  


  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(1.0, 0.0, 0.0, 1.0);

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    draw_ui();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glfwTerminate();
  
}
