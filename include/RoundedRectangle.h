//CLASSE GERADA POR IA

#ifndef ROUNDED_RECTANGLE_H
#define ROUNDED_RECTANGLE_H

#include <glm/glm.hpp>
#include <vector>

class RoundedRectangle
{
private:
    enum class SegmentType
    {
        LINE,
        ARC
    };

    struct Segment
    {
        SegmentType type;

        float length;

        glm::vec3 p0;
        glm::vec3 p1;

        glm::vec3 center;

        float radius;
        float startAngle;
    };

    float width;
    float height;
    float radius;
    float totalLength;

    std::vector<Segment> segments;

    void build();

    int findSegment(float distance, float& localDistance) const;

public:
    RoundedRectangle(
        float width = 20.0f,
        float height = 14.0f,
        float radius = 1.0f
    );

    glm::vec3 position(float distance) const;

    glm::vec3 direction(float distance) const;

    std::vector<glm::vec3> getPositions(int numberOfPositions) const;

    float length() const;

    float getWidth() const;
    float getHeight() const;
    float getRadius() const;
};

#endif