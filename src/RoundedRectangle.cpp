//CLASSE GERADA POR IA

#include "../include/RoundedRectangle.h"

#include <glm/gtc/constants.hpp>

#include <algorithm>
#include <cmath>


RoundedRectangle::RoundedRectangle(
    float width,
    float height,
    float radius
)
    : width(width),
      height(height),
      radius(std::min(radius, std::min(width, height) / 2.0f)),
      totalLength(0.0f)
{
    build();
}


void RoundedRectangle::build()
{
    segments.clear();

    const float r = radius;

    const float x0 = -width / 2.0f + r;
    const float x1 =  width / 2.0f - r;

    const float z0 = -height / 2.0f + r;
    const float z1 =  height / 2.0f - r;

    const float straightWidth = width - 2.0f * r;
    const float straightHeight = height - 2.0f * r;

    const float arcLength = glm::half_pi<float>() * r;


    // 1. Linha superior
    segments.push_back({
        SegmentType::LINE,
        straightWidth,
        { x0, 0.0f, -height / 2.0f },
        { x1, 0.0f, -height / 2.0f },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
        0.0f
    });


    // 2. Arco superior direito
    segments.push_back({
        SegmentType::ARC,
        arcLength,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { x1, 0.0f, z0 },
        r,
        -glm::half_pi<float>()
    });


    // 3. Linha direita
    segments.push_back({
        SegmentType::LINE,
        straightHeight,
        { width / 2.0f, 0.0f, z0 },
        { width / 2.0f, 0.0f, z1 },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
        0.0f
    });


    // 4. Arco inferior direito
    segments.push_back({
        SegmentType::ARC,
        arcLength,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { x1, 0.0f, z1 },
        r,
        0.0f
    });


    // 5. Linha inferior
    segments.push_back({
        SegmentType::LINE,
        straightWidth,
        { x1, 0.0f, height / 2.0f },
        { x0, 0.0f, height / 2.0f },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
        0.0f
    });


    // 6. Arco inferior esquerdo
    segments.push_back({
        SegmentType::ARC,
        arcLength,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { x0, 0.0f, z1 },
        r,
        glm::half_pi<float>()
    });


    // 7. Linha esquerda
    segments.push_back({
        SegmentType::LINE,
        straightHeight,
        { -width / 2.0f, 0.0f, z1 },
        { -width / 2.0f, 0.0f, z0 },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
        0.0f
    });


    // 8. Arco superior esquerdo
    segments.push_back({
        SegmentType::ARC,
        arcLength,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { x0, 0.0f, z0 },
        r,
        glm::pi<float>()
    });


    totalLength = 0.0f;

    for (const Segment& segment : segments)
    {
        totalLength += segment.length;
    }
}


int RoundedRectangle::findSegment(
    float distance,
    float& localDistance
) const
{
    distance = std::fmod(distance, totalLength);

    if (distance < 0.0f)
    {
        distance += totalLength;
    }

    float accumulated = 0.0f;

    for (int i = 0; i < static_cast<int>(segments.size()); ++i)
    {
        const Segment& segment = segments[i];

        if (distance < accumulated + segment.length)
        {
            localDistance = distance - accumulated;
            return i;
        }

        accumulated += segment.length;
    }

    localDistance = 0.0f;

    return 0;
}


glm::vec3 RoundedRectangle::position(float distance) const
{
    float localDistance;

    int index = findSegment(distance, localDistance);

    const Segment& segment = segments[index];

    float u = localDistance / segment.length;


    if (segment.type == SegmentType::LINE)
    {
        return segment.p0 +
               (segment.p1 - segment.p0) * u;
    }


    float theta =
        segment.startAngle +
        u * glm::half_pi<float>();

    return segment.center +
           glm::vec3(
               segment.radius * std::cos(theta),
               0.0f,
               segment.radius * std::sin(theta)
           );
}


glm::vec3 RoundedRectangle::direction(float distance) const
{
    float localDistance;

    int index = findSegment(distance, localDistance);

    const Segment& segment = segments[index];


    if (segment.type == SegmentType::LINE)
    {
        return glm::normalize(
            segment.p1 - segment.p0
        );
    }


    float u = localDistance / segment.length;

    float theta =
        segment.startAngle +
        u * glm::half_pi<float>();

    return glm::normalize(
        glm::vec3(
            -std::sin(theta),
            0.0f,
            std::cos(theta)
        )
    );
}

float RoundedRectangle::length() const
{
    return totalLength;
}


float RoundedRectangle::getWidth() const
{
    return width;
}


float RoundedRectangle::getHeight() const
{
    return height;
}


float RoundedRectangle::getRadius() const
{
    return radius;
}