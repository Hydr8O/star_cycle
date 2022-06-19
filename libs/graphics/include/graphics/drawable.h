#pragma once

#include <glm/glm.hpp>

class Drawable {
private:
    glm::dvec2 m_position;
public:
    virtual void draw();
    void set_position(glm::dvec2 position);
};