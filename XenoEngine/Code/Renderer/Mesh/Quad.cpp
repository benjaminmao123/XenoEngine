#include "pch.h"
#include "Quad.h"

Xeno::Quad::Quad(const uint32_t topology) :
    Mesh(topology)
{
    Vertex vertex[4];

    vertex[0].mPosition = { -1.0f, 1.0f, 0.0f };
    vertex[1].mPosition = { 1.0f, 1.0f, 0.0f };
    vertex[2].mPosition = { -1.0f, -1.0f, 0.0f };
    vertex[3].mPosition = { 1.0f, -1.0f, 0.0f };

    for (auto& i : vertex)
        i.mColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    vertex[0].mUV = { 0.0f, 1.0f };
    vertex[1].mUV = { 1.0f, 1.0f };
    vertex[2].mUV = { 0.0f, 0.0f };
    vertex[3].mUV = { 1.0f, 0.0f };

    for (const auto& i : vertex)
        mVertices.emplace_back(i);

    mIndices = { 0, 1, 2, 1, 2, 3 };
}