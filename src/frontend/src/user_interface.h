#pragma once
#include <string>
#include <vector>

struct Issue
{
  std::string user{" example username"};
  std::string desc{ "hello this is an example descriptiong"};
  std::string title{" CHAMGE THIS ABOUT THE BOBR SOCIETY"};
  std::string location;
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
};
