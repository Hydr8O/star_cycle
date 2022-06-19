#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "paths.h"
#include <shader/shader_program.h>

#include <iostream>
#include <vector>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
   // make sure the viewport matches the new window dimensions; note that width and 
   // height will be significantly larger than specified on retina displays.
   std::cout << width << " " << height << std::endl;
   glViewport(0, 0, width, height);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct GLFWScopeGuard {
   ~GLFWScopeGuard() { glfwTerminate(); }
};

int main(int /*argc*/, char** /*argv[]*/) {

   // glfw: initialize and configure
   // ------------------------------
   glfwInit();
   GLFWScopeGuard scopeGuard{};
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   // glfw window creation
   // --------------------
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
   if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: load all OpenGL function pointers
   // ---------------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }

   // Clobal configuration.
   glfwSwapInterval(1);
   glEnable(GL_DEPTH_TEST);
   //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

   // build and compile our shader program
   ShaderProgram shaderProgram{};
   std::string vertexShaderPath = "vertex_shader.vert";
   std::string fragmentShaderPath = "fragment_shader.frag";
   shaderProgram.loadVertexShaderFromPath(PATH_PREFIX + vertexShaderPath);
   shaderProgram.loadFragmentShaderFromPath(PATH_PREFIX + fragmentShaderPath);
   shaderProgram.linkShaders();

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------

   std::vector<float> vertexData{
      -0.5, -0.5, 0.,
       0.5, -0.5, 0.,
       0.0,  0.5, 0.,
   };
   std::vector<int> indices{
      0, 1, 2
   };
   unsigned int VBO, VAO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

   // Position.
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   GLsizei numVertices = (GLsizei)(indices.size());

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   glBindVertexArray(0);


   // uncomment this call to draw in wireframe polygons.
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // Render loop.
   // -----------
   while (!glfwWindowShouldClose(window)) {
      // Clear.
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // render

      // draw our first triangle
      shaderProgram.use();

      glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      //glDrawArrays(GL_TRIANGLES, 0, 6);
      glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
      // glBindVertexArray(0); // no need to unbind it every time 

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteBuffers(1, &EBO);
   //glDeleteProgram (shaderProgram);

   // glfw: terminate, clearing all previously allocated GLFW resources.
   // ------------------------------------------------------------------
   return 0;
}



