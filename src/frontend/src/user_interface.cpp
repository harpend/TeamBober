#include "user_interface.h"
#include <cstdlib>
#include <print>
#include "bb_images.h"
#include "imgui.h"
#include <filesystem>
#include <format>
#include <string.h>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "../api/backend_api.h"
#include "imgui_internal.h"

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



  // load every file in backend static
  std::filesystem::path dir = "assets/static/uploads/";
  std::ranges::for_each(
    std::filesystem::directory_iterator{dir},
    [this](std::filesystem::path dir_entry) {
      std::println("{}", dir_entry.c_str());
      BB_Image img;
      bb_utils::load_from_file(dir_entry.c_str(), &img.rid, &img.width, &img.height);
      renderer::path_to_img[dir_entry.filename().c_str()] = img;
    }
  );


  for (int i = 0; i < 5; i++)
  {
    BB_Image img;
    bb_utils::load_from_file(std::string("assets/").append(renderer::enum_to_bobr[i]).c_str(), &img.rid, &img.width, &img.height);
    renderer::path_to_img[renderer::enum_to_bobr[i].c_str()] = img;
  }
   

  
  nlohmann::json every_entry= nlohmann::json::parse(BackendAPI::get_issues());
  for (int i = 0; i < every_entry.size(); i++)
  {
    nlohmann::json json_data = every_entry[i];
    Issue issue;
    std::string desc = json_data["description"];
    std::string title= json_data["title"];
    std::string author= json_data["nickname"];
    std::string id_str = json_data["issue_id"];

    std::println("issue id {}", id_str);
    
    strcpy(issue.desc, desc.c_str());
    strcpy(issue.title, title.c_str());
    strcpy(issue.author, author.c_str());
    strcpy(issue.id, id_str.c_str());
    // issue.id = renderer::issues.size();
    issue.upvotes = json_data["upvotes"];
    issue.idx = renderer::issues.size();

    auto& paths = json_data["images"];

    for (auto& p : paths)
    {
      issue.paths.push_back(p);
    }
    
  
    renderer::issues.push_back(issue);
  }

}

void renderer::load_issues() 
{
  renderer::isssues.clear();
  for (int i = 0; i < every_entry.size(); i++)
  {
    nlohmann::json json_data = every_entry[i];
    Issue issue;
    std::string desc = json_data["description"];
    std::string title= json_data["title"];
    std::string author= json_data["nickname"];
    strcpy(issue.desc, desc.c_str());
    strcpy(issue.title, title.c_str());
    strcpy(issue.author, author.c_str());
    issue.id = renderer::issues.size();

    auto& paths = json_data["images"];

    for (auto& p : paths)
    {
      issue.paths.push_back(p);
    }
    
  
    renderer::issues.push_back(issue);
  }
}

void renderer::shutdown()
{
  
}

void renderer::load_all_images()
{
}

// void renderer::add_issue()
// {
 
//   nlohmann::json json_data= nlohmann::json::parse(BackendAPI::get_random_issue());

//   Issue issue;
//   std::string desc = json_data["description"];
//   std::string title= json_data["title"];
//   std::string author= json_data["nickname"];
//   strcpy(issue.desc, desc.c_str());
//   strcpy(issue.title, title.c_str());
//   strcpy(issue.author, author.c_str());
//   issue.id = renderer::issues.size();
  
//   renderer::issues.push_back(issue);
// }

void renderer::draw_ui()
{
  
  draw_dockspace();

  draw_community_feed();
  draw_create_issue();
  draw_saved_issues();


  ImGui::Begin("Upgrade Bobr");
  static bober_fits output{bober_fits::POORBOBR};
  static uint8_t unlocked_bobrs = 1;
  static int item_current = 0;

  // if (ImGui::Button("unlocked next bobr"))

  // ImGui::Enum
  if (unlocked_bobrs != 5)
  {
    std::string msg = std::format("upgrade bobr using {} bobrbux", renderer::prices[unlocked_bobrs]);

    if (ImGui::Button(msg.c_str()) && renderer::wallet >= renderer::prices[unlocked_bobrs])
    {

      renderer::wallet -= renderer::prices[unlocked_bobrs];
      unlocked_bobrs++;
    
    }


    
    if(ImGui::IsItemHovered())
    {
      if (renderer::wallet < renderer::prices[unlocked_bobrs])
        ImGui::SetTooltip("You dont have enough bobrbux");
    }
  }
  
  // 
  const char* items[] = {"poor bobr", "babushka bobr", "bat bobr", "cool bobr", "fancy bobr"};
  ImGui::Combo("equipped", &item_current, items, unlocked_bobrs);
  

  ImGui::Image((ImTextureID)(intptr_t) renderer::path_to_img[renderer::enum_to_bobr[item_current]].rid, ImVec2{(float) bobr_image.width, (float) bobr_image.height});
  ImGui::End();


  // ImGui::ShowDemoWindow();

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
        static char dummy_pwd_buff[50] = {0};

        ImGui::InputTextWithHint("##x", "enter username", username_buff, 50);
        ImGui::InputTextWithHint("##xx", "enter password", dummy_pwd_buff, 50, ImGuiInputTextFlags_Password);

        if (ImGui::Button("login"))
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
      if (ImGui::BeginMenu("Donate"))
      {
        ImGui::Text("bobr-app v0.1.0");
        ImGui::Text("by team-bober");
        ImGui::SameLine();
        ImGui::TextLinkOpenURL("(donate)", "https://beavertrust.org/");
      
        ImGui::EndMenu();
      }
      
      ImGui::Separator();
      if (ImGui::BeginMenu("Refresh"))
      {
        ImGui::Text("bobr-app v0.1.0");
        ImGui::Text("by team-bober");
        ImGui::SameLine();
        ImGui::TextLinkOpenURL("(donate)", "https://beavertrust.org/");
      
        ImGui::EndMenu();
      }


      if (strcmp(renderer::username, "king-bobr") == 0)
      {

        ImGui::Separator();
        if (ImGui::BeginMenu("Debug"))
        {
          if (ImGui::Button("add 100 bobrbux"))
          {
            renderer::wallet += 100;
          }
      
          ImGui::EndMenu();
        }
        // ImGui::Separator();
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
  static float cooldown = 0.0;
  
  ImGui::Begin("Community Feed", NULL, ImGuiWindowFlags_NoScrollbar);
  if (ImGui::Button("Refresh")) {
    load_issues();
  }
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


  static char dummy[100];
  static uint32_t attachs = 0;
  
  if(ImGui::InputText("add image paths", dummy, 50, ImGuiInputTextFlags_EnterReturnsTrue))
  {
    memset(dummy, 0, 100);
    attachs++;
    ImGui::FocusItem();
  }

  ImGui::Text("attatchments: %d", attachs);
  
  if (ImGui::Button("create issue"))
  {
    strcpy(new_issue.author, renderer::username);
    renderer::issues.push_back(new_issue);
    new_issue = {};
    attachs = 0;
  }
    
  ImGui::End();
}

void renderer::draw_saved_issues()
{
  
  ImGui::Begin("My Impact");
  for (Issue& issue : renderer::my_issues)
  {
    draw_my_issue(issue);
  }
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

  if (ImGui::GetContentRegionMax().x > 300)
  {
    std::string credits = std::format("by: {}", issue.author);
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize(credits.c_str()).x);
    ImGui::Text("by: %s", issue.author);
  }
  
  ImGui::TextWrapped("%s", issue.desc);
  ImGui::Text("community support: %d", issue.upvotes);


  ImGui::PushID(issue.idx);
  if(ImGui::ArrowButton("##up", ImGuiDir_Up))
  {
    issue.upvotes++;
    std::string is = issue.id;
    BackendAPI::voteIssue(is);
    
    std::println("{}", issue.id);
  }
  ImGui::PopID();


  if (ImGui::GetContentRegionMax().x > 300)
  {
    ImGui::PushID(issue.idx);
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize("apply to sort").x);
    
    if(ImGui::Button("apply to sort"))
    {
      //TODO: refresh using api endpoint
      renderer::my_issues.push_back(issue);
    }
    ImGui::PopID();
  }


  ImGui::PushID(issue.idx);
  
  if (ImGui::CollapsingHeader("Media", ImGuiTreeNodeFlags_DefaultOpen))
  {


    for (int i = 0; i < issue.paths.size(); i++)
    {
      BB_Image img = renderer::path_to_img[issue.paths[i]];
      ImGui::Image((ImTextureID)(intptr_t) img.rid, ImVec2{(float) img.width / 1.0f, (float) img.height / 1.0f});

      if (i != issue.paths.size() -1)
      {
        ImGui::SameLine();
      }
    }


    if (issue.paths.size() == 0)
    {
      BB_Image img = renderer::path_to_img["pothole.jpg"];
      ImGui::Image((ImTextureID)(intptr_t) img.rid, ImVec2{(float) img.width / 1.0f, (float) img.height / 1.0f});
    }
  }

  ImGui::PopID();
  
  ImGui::Separator();
}


void renderer::draw_my_issue(Issue& issue)
{
  ImGui::Separator();

  ImGui::Text("%s", issue.title);

  if (ImGui::GetContentRegionMax().x > 300)
  {
    std::string credits = std::format("by: {}", issue.author);
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize(credits.c_str()).x);
    ImGui::Text("by: %s", issue.author);
  }
  
  ImGui::TextWrapped("%s", issue.desc);
  ImGui::Text("community support: %d", issue.upvotes);



  if (ImGui::GetContentRegionMax().x > 300)
  {
    ImGui::PushID(issue.id);
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - ImGui::CalcTextSize("completed issue!  ").x);
    
    if(ImGui::Button("completed issue!"))
    {
      renderer::wallet += 10 * issue.upvotes;
    }
    ImGui::PopID();
  }


  ImGui::PushID(issue.id);
  
  if (ImGui::CollapsingHeader("Media", ImGuiTreeNodeFlags_DefaultOpen))
  {


    for (int i = 0; i < issue.paths.size(); i++)
    {
      BB_Image img = renderer::path_to_img[issue.paths[i]];
      ImGui::Image((ImTextureID)(intptr_t) img.rid, ImVec2{(float) img.width / 1.0f, (float) img.height / 1.0f});

      if (i != issue.paths.size() -1)
      {
        ImGui::SameLine();
      }
    }


    if (issue.paths.size() == 0)
    {
      BB_Image img = renderer::path_to_img["pothole.jpg"];
      ImGui::Image((ImTextureID)(intptr_t) img.rid, ImVec2{(float) img.width / 1.0f, (float) img.height / 1.0f});
    }
  }

  ImGui::PopID();
  
  ImGui::Separator();
}
