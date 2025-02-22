workspace "bober-ui"
   configurations { "debug", "release" }

project "bober-ui"
   kind "ConsoleApp"
   
   language "C++"
   cppdialect "C++23"
   
   targetdir "build/bin/%{cfg.buildcfg}"
   objdir "build/obj/%{cfg.buildcfg}"
   
   files {
      "**.h",
      "**.cpp",
      "vendor/glad/src/glad.c",

      "vendor/imgui/*.cpp",
      "vendor/imgui/backends/imgui_impl_glfw.cpp",
      "vendor/imgui/backends/imgui_impl_opengl3.cpp",
   }

  removefiles
  {
    "vendor/imgui/backends/imgui_impl_win32.h",
    "vendor/imgui/backends/imgui_impl_win32.cpp",
  }
   
   includedirs
   {
      "vendor/glad/include",
      "vendor/glfw/include",
      "vendor/imgui/",
      "vendor/glm/",
   }

   links
   {
       "glfw",
   }

  -- only for me!
   postbuildcommands {
     "premake export-compile-commands",
   }
   -- end only for me
   
   filter "configurations:debug"
      defines { "BB_DEBUG" }
      symbols "On"

   filter "configurations:release"
      defines { "BB_NDEBUG" }
      optimize "On"


project "glfw"
    location "vendor/glfw"
    kind "StaticLib"
    targetdir ("build/lib/bin/%{cfg.buildcfg}")
    objdir("build/lib/obj/%{cfg.buildcfg}")

    includedirs
    {
        "vendor/glfw/include",
    }

    defines {
        -- "_GLFW_WIN32" IF USING WINDOWS
        "_GLFW_X11",
    }

    files
    {
        "vendor/glfw/src/**.c",
    }

