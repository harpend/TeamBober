#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

// enum cxxxlass bober_fits
// {
//   NONE,
  
// }

struct Issue
{
  char author[50] {0};
  char desc[500] {0};
  char title[50] {0};
  char location[15] {0};
  uint8_t status {0};
  uint32_t id {0};
  uint32_t upvotes {0};


  std::vector<std::string> paths{};
  
};


struct BB_Image
{
  uint32_t rid{0};
  int  width{0}, height{0};
};


class renderer
{
public:
  void init();
  void shutdown();
  void draw_ui();
private:
  void draw_dockspace();
  void draw_menu_bar();
  void draw_community_feed();
  void draw_create_issue();
  void draw_saved_issues();
  void draw_issue(Issue& issue);
  void load_all_images();
  void load_issues();
private:
  std::vector<Issue> issues;
  std::vector<BB_Image> images;
  std::unordered_map<std::string, BB_Image> path_to_img;

  BB_Image bobr_image;
  char username[50] {"guest"};
  uint32_t wallet{0};
};
