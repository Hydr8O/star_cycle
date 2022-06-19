#pragma once

#include <graphics/drawable.h>
#include <shader/shader_program.h>
#include <glad/glad.h>

class Circle : public Drawable {
public:
   double m_r{0};
   unsigned int m_VAO;
   unsigned int m_EBO;
   unsigned int m_VBO;
   ShaderProgram m_shaderProgram{};
   GLsizei m_numVertices;
   int m_locModel;
   int m_locView;
   int m_locProj;

   Circle();
   ~Circle();
   void draw(glm::dmat4 proj) override;
private:
};

