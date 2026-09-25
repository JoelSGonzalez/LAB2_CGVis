// CLASSE GERADA POR IA

#ifndef DIAMOND_H
#define DIAMOND_H

#include <glm/glm.hpp>
#include <vector>

class Diamond
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
        float angleDelta;
    };

    float width;
    float height;
    float radius;
    float totalLength;

    std::vector<Segment> segments;

    void build();

    int findSegment(
        float distance,
        float& localDistance
    ) const;

public:
    Diamond(
        float width = 6.0f,
        float height = 4.2f,
        float radius = 0.3f
    );

    glm::vec3 position(float distance) const;

    glm::vec3 direction(float distance) const;

    float length() const;

    float getWidth() const;
    float getHeight() const;
    float getRadius() const;
};

#endif