
#include "ShaderProgram.h"


#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void ShaderProgram::loadVertexShaderFromPath(std::string vertexCodePath) {
   std::ifstream ifs(vertexCodePath);
   std::string vertexCode((std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>()));
   if (vertexCode == "") {
      std::cout << "ERROR: Could not find file at: " << vertexCodePath << std::endl;
      throw std::runtime_error("ERROR: Could not find file at: " + vertexCodePath);
   }
   loadVertexShader(vertexCode);
}

void ShaderProgram::loadFragmentShaderFromPath(std::string fragmentCodePath) {
   std::ifstream ifs(fragmentCodePath);
   std::string fragmentCode((std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>()));
   if (fragmentCode == "") {
      std::cout << "ERROR: Could not find file at: " << fragmentCodePath << std::endl;
      throw std::runtime_error("ERROR: Could not find file at: " + fragmentCodePath);
   }
   loadFragmentShader(fragmentCode);
}

void ShaderProgram::loadTessellationControlShaderFromPath(std::string tessContrCodePath) {
   std::ifstream ifs(tessContrCodePath);
   std::string tessCode((std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>()));
   if (tessCode == "") {
      std::cout << "ERROR: Could not find file at: " << tessContrCodePath << std::endl;
      throw std::runtime_error("ERROR: Could not find file at: " + tessContrCodePath);
   }
   loadTessellationControlShader(tessCode);
}

void ShaderProgram::loadTessellationEvaluationShaderFromPath(std::string tessEvalCodePath) {
   std::ifstream ifs(tessEvalCodePath);
   std::string tessCode((std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>()));
   if (tessCode == "") {
      std::cout << "ERROR: Could not find file at: " << tessEvalCodePath << std::endl;
      throw std::runtime_error("ERROR: Could not find file at: " + tessEvalCodePath);
   }
   loadTessellationEvaluationShader(tessCode);
}

void ShaderProgram::loadVertexShader(std::string vertexCode) {
   // vertex shader
   m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
   const char* vertCode = vertexCode.c_str();
   glShaderSource(m_vertexShader, 1, &vertCode, NULL);
   glCompileShader(m_vertexShader);
   // Check for shader compile errors.
   int success;
   char infoLog[512];
   glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR: SHADER::VERTEX::COMPILATION_FAILED.");
   }
   m_vertexShaderIsLoaded = true;
}

void ShaderProgram::loadFragmentShader(std::string fragmentCode) {
   // fragment shader
   m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   const char* fragCode = fragmentCode.c_str();
   glShaderSource(m_fragmentShader, 1, &fragCode, NULL);
   glCompileShader(m_fragmentShader);
   // Check for shader compile errors.
   int success;
   char infoLog[512];
   glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR: SHADER::FRAGMENT::COMPILATION_FAILED.");
   }
   m_fragmentShaderIsLoaded = true;
}

void ShaderProgram::loadTessellationControlShader(std::string tessContrCode) {
   // Tesselation control shader.
   m_tessellationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
   const char* tessCode = tessContrCode.c_str();
   glShaderSource(m_tessellationControlShader, 1, &tessCode, NULL);
   glCompileShader(m_tessellationControlShader);
   // Check for shader compile errors.
   int success;
   char infoLog[512];
   glGetShaderiv(m_tessellationControlShader, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(m_tessellationControlShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::TESS_CONTR::COMPILATION_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR: SHADER::TESS_CONTR::COMPILATION_FAILED.");
   }
   m_tessellationControlShaderIsLoaded = true;
}

void ShaderProgram::loadTessellationEvaluationShader(std::string tessEvalCode) {
   // Tesselation evaluation shader.
   m_tessellationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
   const char* tessCode = tessEvalCode.c_str();
   glShaderSource(m_tessellationEvaluationShader, 1, &tessCode, NULL);
   glCompileShader(m_tessellationEvaluationShader);
   // Check for shader compile errors.
   int success;
   char infoLog[512];
   glGetShaderiv(m_tessellationEvaluationShader, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(m_tessellationEvaluationShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::TESS_EVAL::COMPILATION_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR: SHADER::TESS_EVAL::COMPILATION_FAILED.");
   }
   m_tessellationEvaluationShaderIsLoaded = true;
}

void ShaderProgram::linkShaders() {
   if (!m_vertexShaderIsLoaded) {
      throw std::runtime_error("ERROR: Cannot link shader program before loading vertex shader.");
   }
   if (!m_fragmentShaderIsLoaded) {
      throw std::runtime_error("ERROR: Cannot link shader program before loading fragment shader.");
   }
   //if (!m_tesselationControlShaderIsLoaded) {
   //   throw std::runtime_error (
   //      "ERROR: Cannot link shader program before loading tesselation shader."
   //   );
   //}
   //if (!m_tesselationEvaluationShaderIsLoaded) {
   //   throw std::runtime_error (
   //      "ERROR: Cannot link shader program before loading tesselation shader."
   //   );
   //}
   // link shaders
   m_shaderProgram = glCreateProgram();
   glAttachShader(m_shaderProgram, m_vertexShader);
   glAttachShader(m_shaderProgram, m_fragmentShader);
   if (m_tessellationControlShaderIsLoaded) {
      glAttachShader(m_shaderProgram, m_tessellationControlShader);
   }
   if (m_tessellationEvaluationShaderIsLoaded) {
      glAttachShader(m_shaderProgram, m_tessellationEvaluationShader);
   }
   glLinkProgram(m_shaderProgram);
   // check for linking errors
   int success;
   char infoLog[512];
   glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR: SHADER::PROGRAM::LINKING_FAILED.");
   }
   glDeleteShader(m_vertexShader);
   glDeleteShader(m_fragmentShader);
   if (m_tessellationControlShaderIsLoaded) {
      glDeleteShader(m_tessellationControlShader);
   }
   if (m_tessellationEvaluationShaderIsLoaded) {
      glDeleteShader(m_tessellationEvaluationShader);
   }
   m_programIsLinked = true;
}

unsigned int ShaderProgram::getID() {
   if (m_programIsLinked) {
      return m_shaderProgram;
   }
   throw std::runtime_error("ERROR: Shader program is not linked.");
}

void ShaderProgram::use() {
   if (!m_programIsLinked) {
      throw std::runtime_error("ERROR: Cannot use a program before it is linked.");
   }
   glUseProgram(m_shaderProgram);
}

ShaderProgram::~ShaderProgram() {
   if (m_programIsLinked) {
      glDeleteProgram(m_shaderProgram);
   }
   else {
      if (m_vertexShader != 0) {
         // 0 means it is not created yet.
         glDeleteShader(m_vertexShader);
      }
      if (m_fragmentShader != 0) {
         // 0 means it is not created yet.
         glDeleteShader(m_fragmentShader);
      }
      if (m_tessellationControlShader != 0) {
         // 0 means it is not created yet.
         glDeleteShader(m_tessellationControlShader);
      }
      if (m_tessellationEvaluationShader != 0) {
         // 0 means it is not created yet.
         glDeleteShader(m_tessellationEvaluationShader);
      }
   }
}
