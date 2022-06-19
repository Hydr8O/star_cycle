#include <graphics/circle.h>

#include <paths.h>
#include <vector>
#include <glad/glad.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Circle::Circle() {
   std::string vertexShaderPath = "resources/circle_vertex_shader.vert";
   std::string fragmentShaderPath = "resources/circle_fragment_shader.frag";
   m_shaderProgram.loadVertexShaderFromPath(PATH_PREFIX + vertexShaderPath);
   m_shaderProgram.loadFragmentShaderFromPath(PATH_PREFIX + fragmentShaderPath);
   m_shaderProgram.linkShaders();

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------

   std::vector<float> vertexData{
      -1.0, -1.0, 0.,
       1.0, -1.0, 0.,
       1.0,  1.0, 0.,
      -1.0,  1.0, 0.,
   };
   std::vector<int> indices{
      0, 1, 2, 0, 2, 3
   };
   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_VBO);
   glGenBuffers(1, &m_EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

   // Position.
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   m_numVertices = (GLsizei)(indices.size());

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   glBindVertexArray(0);

   m_locModel = glGetUniformLocation(m_shaderProgram.getID(), "model");
   m_locView = glGetUniformLocation(m_shaderProgram.getID(), "view");
   m_locProj = glGetUniformLocation(m_shaderProgram.getID(), "proj");
}

Circle::~Circle() {
   glDeleteVertexArrays(1, &m_VAO);
   glDeleteBuffers(1, &m_VBO);
   glDeleteBuffers(1, &m_EBO);
}

void Circle::draw(glm::dmat4 proj) {
   m_shaderProgram.use();

   glm::dmat4 model{ glm::translate(glm::dmat4(1), m_position) };
   //model = glm::scale(model, glm::dvec3{ glm::sqrt(pp->m_mass) });
   glUniformMatrix4fv(m_locModel, 1, GL_FALSE, glm::value_ptr((glm::mat4)model));
   glUniformMatrix4fv(m_locView, 1, GL_FALSE, glm::value_ptr((glm::mat4)glm::dmat4(1)));
   glUniformMatrix4fv(m_locProj, 1, GL_FALSE, glm::value_ptr((glm::mat4)proj));

   glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
   //glDrawArrays(GL_TRIANGLES, 0, 6);
   glDrawElements(GL_TRIANGLES, m_numVertices, GL_UNSIGNED_INT, 0);
}
