#include "pch.h"
#include "Quad.h"

Xeno::Quad::Quad(const uint32_t topology) :
    Mesh(topology)
{
    mVertices.resize(4);

    mVertices[0].mPosition = { 1.0f, 1.0f, 0.0f };
    mVertices[1].mPosition = { -1.0f, 1.0f, 0.0f };
    mVertices[2].mPosition = { -1.0f, -1.0f, 0.0f };
    mVertices[3].mPosition = { 1.0f, -1.0f, 0.0f };

    for (auto& v : mVertices)
        v.mColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    mVertices[0].mUV = { 1.0f, 1.0f };
    mVertices[1].mUV = { 0.0f, 1.0f };
    mVertices[2].mUV = { 0.0f, 0.0f };
    mVertices[3].mUV = { 1.0f, 0.0f };

    mIndices = { 0, 1, 2, 0, 2, 3 };
}