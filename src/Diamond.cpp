// CLASSE GERADA POR IA

#include "Diamond.h"

#include <cmath>
#include <algorithm>

#include <glm/gtc/constants.hpp>

Diamond::Diamond(float width, float height, float radius)
    : width(width),
      height(height),
      radius(radius),
      totalLength(0.0f)
{
    build();
}

void Diamond::build()
{
    segments.clear();
    totalLength = 0.0f;

    // Vértices do losango:
    //
    //             0
    //            / \
    //           /   \
    //          3     1
    //           \   /
    //            \ /
    //             2
    //
    glm::vec3 vertices[4] =
    {
        glm::vec3(0.0f,        0.0f, -height / 2.0f), // topo
        glm::vec3(width / 2.0f, 0.0f,  0.0f),         // direita
        glm::vec3(0.0f,        0.0f,  height / 2.0f), // baixo
        glm::vec3(-width / 2.0f, 0.0f, 0.0f)          // esquerda
    };

    glm::vec3 tangentBefore[4];
    glm::vec3 tangentAfter[4];
    glm::vec3 centers[4];

    float startAngles[4];
    float endAngles[4];

    // Calcula os pontos de tangência e os centros dos quatro arcos.
    for (int i = 0; i < 4; ++i)
    {
        int previous = (i + 3) % 4;
        int next = (i + 1) % 4;

        glm::vec3 toPrevious =
            glm::normalize(vertices[previous] - vertices[i]);

        glm::vec3 toNext =
            glm::normalize(vertices[next] - vertices[i]);

        float cosTheta =
            glm::dot(toPrevious, toNext);

        if (cosTheta < -1.0f)
            cosTheta = -1.0f;
        else if (cosTheta > 1.0f)
            cosTheta = 1.0f;

        float theta = std::acos(cosTheta);

        // Distância do vértice até cada ponto de tangência.
        float tangentDistance =
            radius / std::tan(theta / 2.0f);

        tangentBefore[i] =
            vertices[i] + toPrevious * tangentDistance;

        tangentAfter[i] =
            vertices[i] + toNext * tangentDistance;

        // Distância do vértice até o centro do arco.
        float centerDistance =
            radius / std::sin(theta / 2.0f);

        glm::vec3 bisector =
            glm::normalize(toPrevious + toNext);

        centers[i] =
            vertices[i] + bisector * centerDistance;

        // Ângulos dos pontos de tangência em relação ao centro.
        glm::vec3 before =
            tangentBefore[i] - centers[i];

        glm::vec3 after =
            tangentAfter[i] - centers[i];

        startAngles[i] =
            std::atan2(before.z, before.x);

        endAngles[i] =
            std::atan2(after.z, after.x);
    }

    // Cria os 8 segmentos:
    //
    // linha -> arco -> linha -> arco -> ...
    //
    for (int i = 0; i < 4; ++i)
    {
        int next = (i + 1) % 4;

        // -------------------------------------------------
        // Linha entre o arco do vértice atual e o próximo
        // -------------------------------------------------

        Segment line;

        line.type = SegmentType::LINE;

        line.p0 = tangentAfter[i];
        line.p1 = tangentBefore[next];

        line.length =
            glm::length(line.p1 - line.p0);

        line.center = glm::vec3(0.0f);
        line.radius = 0.0f;
        line.startAngle = 0.0f;
        line.angleDelta = 0.0f;

        segments.push_back(line);

        totalLength += line.length;

        // -------------------------------------------------
        // Arco do próximo vértice
        // -------------------------------------------------

        Segment arc;

        arc.type = SegmentType::ARC;

        arc.p0 = tangentBefore[next];
        arc.p1 = tangentAfter[next];

        arc.center = centers[next];
        arc.radius = radius;

        arc.startAngle = startAngles[next];

        // O arco deve percorrer a parte externa da curva.
        arc.angleDelta =
            endAngles[next] - startAngles[next];

        while (arc.angleDelta <= 0.0f)
        {
            arc.angleDelta += glm::two_pi<float>();
        }

        arc.length =
            radius * std::abs(arc.angleDelta);

        segments.push_back(arc);

        totalLength += arc.length;
    }
}

int Diamond::findSegment(
    float distance,
    float& localDistance
) const
{
    if (segments.empty())
    {
        localDistance = 0.0f;
        return -1;
    }

    distance =
        std::fmod(distance, totalLength);

    if (distance < 0.0f)
        distance += totalLength;

    float accumulated = 0.0f;

    for (int i = 0; i < static_cast<int>(segments.size()); ++i)
    {
        if (distance < accumulated + segments[i].length)
        {
            localDistance =
                distance - accumulated;

            return i;
        }

        accumulated += segments[i].length;
    }

    // Caso especial para evitar problemas de ponto flutuante.
    localDistance = 0.0f;

    return static_cast<int>(segments.size()) - 1;
}

glm::vec3 Diamond::position(float distance) const
{
    float localDistance = 0.0f;

    int index =
        findSegment(distance, localDistance);

    if (index < 0)
        return glm::vec3(0.0f);

    const Segment& segment =
        segments[index];

    if (segment.type == SegmentType::LINE)
    {
        float t =
            localDistance / segment.length;

        return
            segment.p0 +
            (segment.p1 - segment.p0) * t;
    }

    // -----------------------------------------------------
    // Arco
    // -----------------------------------------------------

    float u =
        localDistance / segment.length;

    float theta =
        segment.startAngle +
        segment.angleDelta * u;

    return segment.center +
           glm::vec3(
               segment.radius * std::cos(theta),
               0.0f,
               segment.radius * std::sin(theta)
           );
}

glm::vec3 Diamond::direction(float distance) const
{
    float localDistance = 0.0f;

    int index =
        findSegment(distance, localDistance);

    if (index < 0)
        return glm::vec3(0.0f);

    const Segment& segment =
        segments[index];

    if (segment.type == SegmentType::LINE)
    {
        return glm::normalize(
            segment.p1 - segment.p0
        );
    }

    // -----------------------------------------------------
    // Tangente ao arco
    // -----------------------------------------------------

    float u =
        localDistance / segment.length;

    float theta =
        segment.startAngle +
        segment.angleDelta * u;

    return glm::normalize(
        glm::vec3(
            -std::sin(theta),
            0.0f,
            std::cos(theta)
        )
    );
}

float Diamond::length() const
{
    return totalLength;
}

float Diamond::getWidth() const
{
    return width;
}

float Diamond::getHeight() const
{
    return height;
}

float Diamond::getRadius() const
{
    return radius;
}