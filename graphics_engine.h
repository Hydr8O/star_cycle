#pragma once

#include <vector>
#include<memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <graphics\drawable.h>

class GraphicsEngine {
public:
   std::vector<std::shared_ptr<Drawable>> m_drawables;
   GLFWwindow* m_window;
   int m_width;
   int m_height;

   GraphicsEngine(int width, int height);
   ~GraphicsEngine();
   bool render();
   void addDrawable(std::shared_ptr<Drawable> drawable);
private:

};

