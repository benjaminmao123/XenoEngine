#include "pch.h"
#include "Plane.h"

Xeno::Plane::Plane(const int32_t xSegments, const int32_t ySegments, const uint32_t topology) :
    Mesh(topology)
{
    bool oddRow = false;

    const float dX = 1.0f / xSegments;
    const float dY = 1.0f / ySegments;

    for (int32_t y = 0; y <= ySegments; ++y)
    {
        for (int32_t x = 0; x <= xSegments; ++x)
        {
            Vertex vertex;

            vertex.mPosition = glm::vec3(dX * x * 2.0f - 1.0f, dY * y * 2.0f - 1.0f, 0.0f);
            vertex.mUV = glm::vec2(dX * x, 1.0f - y * dY);
            vertex.mNormal = glm::vec3(0.0f, 0.0f, 1.0f);
            
            mVertices.emplace_back(vertex);
        }
    }

    for (int32_t y = 0; y < ySegments; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (int32_t x = 0; x <= xSegments; ++x)
            {
                mIndices.emplace_back(y * (xSegments + 1) + x);
                mIndices.emplace_back((y + 1) * (xSegments + 1) + x);
            }
        }
        else
        {
            for (int32_t x = xSegments; x >= 0; --x)
            {
                mIndices.emplace_back((y + 1) * (xSegments + 1) + x);
                mIndices.emplace_back(y * (xSegments + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
}
