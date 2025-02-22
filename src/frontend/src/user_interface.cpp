#include "user_interface.h"
#include <print>
#include "bb_images.h"
#include "imgui.h"
#include <filesystem>
#include <format>

void renderer::init()
{
  std::println("fs: {}", std::filesystem::current_path().c_str());

  bool r = bb_utils::load_from_file("assets/bobr.png", &bobr_image.rid, &bobr_image.width, &bobr_image.height);
  std::println("loaded? {}", r);


  
  ImGui::StyleColorsDark();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  ImFont* f = io.Fonts->AddFontFromFileTTF("assets/jetbrains.ttf", 25);

  ImGui::GetStyle().WindowMenuButtonPosition = ImGuiDir_None;
  ImGui::GetStyle().ScaleAllSizes(1.5);

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


  ImGui::Begin("Upgrade Bobr");
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
    
      std::string fmt = std::format("({})", renderer::username);

      if (ImGui::BeginMenu(fmt.c_str()))
      {
        static char username_buff[50] = {0};
        ImGui::Text("change username");
        if (ImGui::InputTextWithHint("##", "enter here", username_buff, 50, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
        {
          memcpy(renderer::username, username_buff, 50);
        }
      
        ImGui::EndMenu();
      }

      ImGui::Separator();
      
      if (ImGui::BeginMenu("Community"))
      {
        ImGui::Text("current: Birmingham Community");
        ImGui::Text("invite code: BR2025");
        ImGui::Button("exit");
      
        ImGui::EndMenu();
      }

      ImGui::Separator();
      
      if (ImGui::BeginMenu("About"))
      {
        ImGui::Text("bobr-app v0.1.0");
        ImGui::Text("by team-bober");
        ImGui::SameLine();
        ImGui::TextLinkOpenURL("(repo)", "https://github.com/harpend/TeamBober");
      
        ImGui::EndMenu();
      }


      ImGui::Separator();

      ImGui::Text("Currency: %d bobrbux", wallet);
        
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
  static Issue new_issue;
  
  ImGui::Begin("Create Issue");

  ImGui::InputText("title", new_issue.title, 50);
  ImGui::InputTextMultiline("description", new_issue.desc, 500, ImVec2{0, 0});
  ImGui::InputText("location", new_issue.location, 15);
  ImGui::Button("add media");
  ImGui::Button("create issue");
    
  ImGui::End();
}

void renderer::draw_saved_issues()
{
  
  ImGui::Begin("My Impact");
  ImGui::Text("example start\n\n\n\n\nexample end");
  ImGui::End();
}

/*
title
desc
author
status
media
location
*/

void renderer::draw_issue(Issue& issue)
{
  ImGui::Separator();

  ImGui::Text("%s", issue.title);
  ImGui::TextWrapped("%s", issue.desc);
  ImGui::Text("by: %s", issue.author);
  
  ImGui::Separator();
}
