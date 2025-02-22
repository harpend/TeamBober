#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Issue
{
  char author[50] {"John Doe"};
  char desc[500] { "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras et nibh erat. Integer turpis orci, tempus id quam eu, posuere blandit risus. Integer sed tincidunt magna, ut porta enim. Donec imperdiet placerat augue, vel maximus ante placerat id."};
  char title[50] {"Loren ipsum"};
  char location[15];
  uint8_t status;
  uint32_t id;
  uint32_t upvotes;
  
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
  void add_issue();
  void load_all_images();
private:
  std::vector<Issue> issues;
  std::vector<BB_Image> images;

  BB_Image bobr_image;
  char username[50] {"guest"};
  uint32_t wallet{0};
};
