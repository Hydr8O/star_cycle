
#include <graphics_engine.h>
#include <graphics/circle.h>
#include <iostream>

int main(int /*argc*/, char** /*argv[]*/) {

   GraphicsEngine graphicsEngine{600, 400};
   std::shared_ptr<Drawable> circle = std::make_shared<Circle>();
   graphicsEngine.addDrawable(circle);
   while (graphicsEngine.render()) {
      
   }

   // glfw: terminate, clearing all previously allocated GLFW resources.
   // ------------------------------------------------------------------
   return 0;
}



