#include "user_interface.h"
#include <print>
#include "bb_images.h"
#include "imgui.h"
#include <filesystem>

void renderer::init()
{
  std::print("fs: {}", std::filesystem::current_path().c_str());

  bool r = bb_utils::load_from_file("assets/bobr.png", &bobr_image.rid, &bobr_image.width, &bobr_image.height);
  std::print("loaded? {}", r);

}

void renderer::shutdown()
{
  
}

void renderer::draw_ui()
{
  
  draw_dockspace();

  draw_community_feed();
  draw_create_issue();
  draw_saved_issues();


  ImGui::Begin("bobr image");
  // std::print("{}", bobr_image.rid);
  ImGui::Image((ImTextureID)(intptr_t) bobr_image.rid, ImVec2{(float) bobr_image.width, (float) bobr_image.height});
  ImGui::End();


  ImGui::ShowDemoWindow();

}



void renderer::draw_dockspace()
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

  draw_menu_bar();
}


void renderer::draw_menu_bar()
{
  
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

void renderer::draw_community_feed()
{
  
  ImGui::Begin("Community Feed");

  for (auto& issue : issues)
  {
    draw_issue(issue);
  }
  
  ImGui::End();
}

void renderer::draw_create_issue()
{
  
  ImGui::Begin("Create Issue");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();
}

void renderer::draw_saved_issues()
{
  
  ImGui::Begin("Saved Issues");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();
}

void renderer::draw_issue(Issue& issue)
{
  ImGui::Separator();
  ImGui::Text("%s", issue.title.c_str());
  ImGui::TextWrapped("%s", issue.desc.c_str());
  ImGui::Text("by: %s", issue.user.c_str());
  ImGui::Separator();
}
