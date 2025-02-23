# frontend
ImGui is a immediate mode.  
This means that every frame the structure of all the user interface in your window is rebuilt from scratch.  
We decided to use ImGui as we had some experience already using it and its easier to pick up than a retained mode ui.  

As ImGui is intended for real time graphics applications we had to open a window on our own and setup a graphics API, but this wasnt too hard in OpenGL so after a bit of setup we just needed to have a draw_ui() entry point and forget about the implementation data.  

## procedural style
We kept it simple with, only having a couple functions for the different areas of the ui we are drawing.  
We also used the docking feature to cleanly divide the different areas of functionality.
