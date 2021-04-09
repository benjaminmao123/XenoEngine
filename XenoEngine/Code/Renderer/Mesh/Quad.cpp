#include "pch.h"
#include "Renderer/Mesh/Quad.h"

Xeno::Quad::Quad(const Topology topology) :
    Mesh(topology)
{
    Vertex vertex[sNumVertices];

    vertex[0].mPosition = { -1.0f, 1.0f, 0.0f };
    vertex[1].mPosition = { 1.0f, 1.0f, 0.0f };
    vertex[2].mPosition = { -1.0f, -1.0f, 0.0f };
    vertex[3].mPosition = { 1.0f, -1.0f, 0.0f };

    for (auto& i : vertex)
        i.mColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    vertex[0].mUVs = { 0.0f, 1.0f };
    vertex[1].mUVs = { 1.0f, 1.0f };
    vertex[2].mUVs = { 0.0f, 0.0f };
    vertex[3].mUVs = { 1.0f, 0.0f };

    for (const auto& i : vertex)
        mVertices.emplace_back(i);

    mIndices = { 0, 1, 2, 1, 2, 3 };
}
