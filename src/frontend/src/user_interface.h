#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <array>
#include <unordered_map>

enum class bober_fits : uint8_t
{
  POORBOBR = 1,
  BABUSHKABOBOR = 1 << 1,
  BATBOBR = 1 << 2,
  COOLBOBR = 1 << 3,
  FANCYBOBR = 1 << 4,
};



struct Issue
{
  char author[50] {0};
  char desc[500] {0};
  char title[50] {0};
  char location[15] {0};
  char status[15] {0};
  char id[7];
  uint32_t upvotes {1};
  uint32_t idx{0};


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
  void draw_my_issue(Issue& issue);
  void load_all_images();
  void load_issues();
private:
  std::vector<Issue> issues;
  std::vector<Issue> my_issues;
  
  std::vector<BB_Image> images;
  std::unordered_map<std::string, BB_Image> path_to_img;

  std::array<std::string, 5> enum_to_bobr = {"poor_bobr.jpg", "babushka_bobr.jpg", "batbobr_.png", "cool_bobr.jpg", "fancy_bobr.jpg"};
  uint32_t prices[5] = {0, 100, 350, 700, 1000};


  std::vector<uint32_t> queue_issues{};
  std::vector<uint32_t> queue_my{};

  BB_Image bobr_image;
  char username[50] {"guest"};
  uint32_t wallet{0};
};
