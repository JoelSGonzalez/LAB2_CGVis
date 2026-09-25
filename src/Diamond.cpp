#include "../include/Diamond.h"

#include <glm/gtc/constants.hpp>

#include <algorithm>
#include <cmath>


Diamond::Diamond(
    float width,
    float height,
    float radius
)
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

    /*
        Vértices do losango:

                top
                 /\
                /  \
          left /    \ right
               \    /
                \  /
                 \/
               bottom

        A trajetória percorre:

        top -> right -> bottom -> left -> top
    */

    const glm::vec3 vertices[4] =
    {
        { 0.0f,        0.0f, -height / 2.0f }, // top
        { width / 2.0f, 0.0f,  0.0f        },  // right
        { 0.0f,        0.0f,  height / 2.0f }, // bottom
        {-width / 2.0f, 0.0f,  0.0f        }   // left
    };


    /*
        Calcula os pontos de tangência e centros
        dos quatro cantos arredondados.
    */

    glm::vec3 tangentBefore[4];
    glm::vec3 tangentAfter[4];
    glm::vec3 centers[4];


    for (int i = 0; i < 4; ++i)
    {
        const glm::vec3& vertex = vertices[i];

        const glm::vec3& previous =
            vertices[(i + 3) % 4];

        const glm::vec3& next =
            vertices[(i + 1) % 4];


        glm::vec3 toPrevious =
            glm::normalize(previous - vertex);

        glm::vec3 toNext =
            glm::normalize(next - vertex);


        /*
            Ângulo interno do vértice.
        */

        float cosTheta =
            glm::dot(toPrevious, toNext);

        cosTheta =
            std::clamp(cosTheta, -1.0f, 1.0f);

        float theta =
            std::acos(cosTheta);


        /*
            Distância entre o vértice e cada ponto
            de tangência.
        */

        float tangentDistance =
            radius / std::tan(theta / 2.0f);


        tangentBefore[i] =
            vertex + toPrevious * tangentDistance;

        tangentAfter[i] =
            vertex + toNext * tangentDistance;


        /*
            Centro do círculo.

            O centro está sobre a bissetriz
            do ângulo interno.
        */

        glm::vec3 bisector =
            glm::normalize(toPrevious + toNext);

        float centerDistance =
            radius / std::sin(theta / 2.0f);

        centers[i] =
            vertex + bisector * centerDistance;
    }


    /*
        Cada lado reto vai do ponto de tangência
        depois de um canto até o ponto de tangência
        antes do próximo canto.
    */

    totalLength = 0.0f;


    for (int i = 0; i < 4; ++i)
    {
        int next =
            (i + 1) % 4;


        // Lado reto

        glm::vec3 p0 =
            tangentAfter[i];

        glm::vec3 p1 =
            tangentBefore[next];

        float lineLength =
            glm::length(p1 - p0);


        segments.push_back({
            SegmentType::LINE,
            lineLength,
            p0,
            p1,
            glm::vec3(0.0f),
            0.0f,
            0.0f,
            0.0f
        });

        totalLength += lineLength;


        // Arco no próximo vértice

        const glm::vec3& center =
            centers[next];

        glm::vec3 start =
            tangentBefore[next] - center;

        glm::vec3 end =
            tangentAfter[next] - center;


        float startAngle =
            std::atan2(start.z, start.x);

        float endAngle =
            std::atan2(end.z, end.x);


        /*
            O losango é percorrido no sentido
            top -> right -> bottom -> left.

            Os arcos precisam seguir o mesmo sentido
            da trajetória.
        */

        float angleDelta =
            endAngle - startAngle;

        while (angleDelta >= 0.0f)
            angleDelta -= glm::two_pi<float>();


        float arcLength =
            radius * std::abs(angleDelta);


        segments.push_back({
            SegmentType::ARC,
            arcLength,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            center,
            radius,
            startAngle,
            angleDelta
        });

        totalLength += arcLength;
    }
}


int Diamond::findSegment(
    float distance,
    float& localDistance
) const
{
    distance =
        std::fmod(distance, totalLength);

    if (distance < 0.0f)
        distance += totalLength;


    float accumulated = 0.0f;


    for (int i = 0;
         i < static_cast<int>(segments.size());
         ++i)
    {
        const Segment& segment =
            segments[i];


        if (distance <
            accumulated + segment.length)
        {
            localDistance =
                distance - accumulated;

            return i;
        }


        accumulated += segment.length;
    }


    localDistance = 0.0f;

    return 0;
}


glm::vec3 Diamond::position(float distance) const
{
    float localDistance;

    int index =
        findSegment(distance, localDistance);

    const Segment& segment =
        segments[index];


    float u =
        localDistance / segment.length;


    if (segment.type == SegmentType::LINE)
    {
        return segment.p0 +
               (segment.p1 - segment.p0) * u;
    }


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
    float localDistance;

    int index =
        findSegment(distance, localDistance);

    const Segment& segment =
        segments[index];


    if (segment.type == SegmentType::LINE)
    {
        return glm::normalize(
            segment.p1 - segment.p0
        );
    }


    float u =
        localDistance / segment.length;

    float theta =
        segment.startAngle +
        segment.angleDelta * u;


    /*
        Derivada da posição do círculo.

        O sinal depende do sentido do arco.
    */

    float sign =
        segment.angleDelta < 0.0f
        ? -1.0f
        : 1.0f;


    return glm::normalize(
        glm::vec3(
            -std::sin(theta) * sign,
            0.0f,
             std::cos(theta) * sign
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