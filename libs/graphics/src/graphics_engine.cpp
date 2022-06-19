#include <graphics/graphics_engine.h>


#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

GraphicsEngine::GraphicsEngine(int width, int height) {
   m_width = width;
   m_height = height;
   // glfw: initialize and configure
   // ------------------------------
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   // glfw window creation
   // --------------------
   m_window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
   if (m_window == NULL) {
      throw "Failed to create GLFW window";
   }
   glfwMakeContextCurrent(m_window);
   //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: load all OpenGL function pointers
   // ---------------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      throw "Failed to initialize GLAD";
   }

   // Clobal configuration.
   glfwSwapInterval(1);
   glEnable(GL_DEPTH_TEST);
   //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
}

GraphicsEngine::~GraphicsEngine() {
   m_drawables.clear();
   glfwTerminate();
}

bool GraphicsEngine::render() {
   if (glfwWindowShouldClose(m_window)) {
      return false;
   }

   // Clear.
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   /*glm::highp_dmat4 proj{ glm::ortho(
      cam.pos.x - cam.zoom * 0.5, cam.pos.x + cam.zoom * 0.5,
      cam.pos.y - cam.zoom * 0.5 / aspectRatio, cam.pos.y + cam.zoom * 0.5 / aspectRatio
   ) };*/

   double aspectRatio{ (double)m_width / (double)m_height};
   double zoom{10.};
   glm::highp_dmat4 proj{ glm::ortho(
      -zoom * 0.5, zoom * 0.5,
      -zoom * 0.5 / aspectRatio, zoom * 0.5 / aspectRatio
   ) };

   for (auto& drawable : m_drawables) {
      drawable->draw(proj);
   }

   // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
   // -------------------------------------------------------------------------------
   glfwSwapBuffers(m_window);
   glfwPollEvents();

   return true;
}

void GraphicsEngine::addDrawable(std::shared_ptr<Drawable> drawable) {
   m_drawables.push_back(drawable);
}
