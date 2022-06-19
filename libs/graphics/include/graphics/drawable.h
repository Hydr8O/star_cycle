#pragma once

#include <glm/glm.hpp>

class Drawable {
private:
public:
   glm::dvec3 m_position{0};
   virtual void draw(glm::dmat4 proj) = 0;
};