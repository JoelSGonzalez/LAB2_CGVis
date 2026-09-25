#ifndef CIRCLE_H
#define CIRCLE_H

#include <glm/glm.hpp>

class Circle
{
private:
    float radius;
    float totalLength;

public:
    Circle(float radius = 3.0f);

    glm::vec3 position(float distance) const;

    glm::vec3 direction(float distance) const;

    float length() const;

    float getRadius() const;
};

#endif