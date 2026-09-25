#include "Circle.h"

#include <cmath>

#include <glm/gtc/constants.hpp>

Circle::Circle(float radius)
    : radius(radius),
      totalLength(glm::two_pi<float>() * radius)
{
}

glm::vec3 Circle::position(float distance) const
{
    // Converte distância percorrida em ângulo.
    float theta =
        std::fmod(distance, totalLength)
        / radius;

    return glm::vec3(
        radius * std::cos(theta),
        0.0f,
        radius * std::sin(theta)
    );
}

glm::vec3 Circle::direction(float distance) const
{
    float theta =
        std::fmod(distance, totalLength)
        / radius;

    // Vetor tangente ao círculo.
    return glm::normalize(
        glm::vec3(
            -std::sin(theta),
            0.0f,
            std::cos(theta)
        )
    );
}

float Circle::length() const
{
    return totalLength;
}

float Circle::getRadius() const
{
    return radius;
}