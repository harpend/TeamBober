#pragma once
#include <string>
#include <vector>
#include <cstdint>

struct Issue
{
  std::string user{"John Doe"};
  std::string desc{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras et nibh erat. Integer turpis orci, tempus id quam eu, posuere blandit risus. Integer sed tincidunt magna, ut porta enim. Donec imperdiet placerat augue, vel maximus ante placerat id."};
  std::string title{"Loren ipsum"};
  std::string location;
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
private:
  std::vector<Issue> issues{100};


  BB_Image bobr_image;
};
