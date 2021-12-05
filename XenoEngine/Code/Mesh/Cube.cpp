#include "pch.h"
#include "Cube.h"

Xeno::Cube::Cube(const uint32_t topology) :
    Mesh(topology)
{
    mVertices.resize(24);

    mVertices[0].mPosition = { -1.0, -1.0, 1.0 };
    mVertices[1].mPosition = { 1.0, -1.0, 1.0 };
    mVertices[2].mPosition = { 1.0, 1.0, 1.0 };
    mVertices[3].mPosition = { -1.0, 1.0, 1.0 };
    mVertices[4].mPosition = { -1.0, 1.0, 1.0 };
    mVertices[5].mPosition = { 1.0, 1.0, 1.0 };
    mVertices[6].mPosition = { 1.0, 1.0, -1.0 };
    mVertices[7].mPosition = { -1.0, 1.0, -1.0 };
    mVertices[8].mPosition = { 1.0, -1.0, -1.0 };
    mVertices[9].mPosition = { -1.0, -1.0, -1.0 };
    mVertices[10].mPosition = { -1.0, 1.0, -1.0 };
    mVertices[11].mPosition = { 1.0, 1.0, -1.0 };
    mVertices[12].mPosition = { -1.0, -1.0, -1.0 };
    mVertices[13].mPosition = { 1.0, -1.0, -1.0 };
    mVertices[14].mPosition = { 1.0, -1.0, 1.0 };
    mVertices[15].mPosition = { -1.0, -1.0, 1.0 };
    mVertices[16].mPosition = { -1.0, -1.0, -1.0 };
    mVertices[17].mPosition = { -1.0, -1.0, 1.0 };
    mVertices[18].mPosition = { -1.0, 1.0, 1.0 };
    mVertices[19].mPosition = { -1.0, 1.0, -1.0 };
    mVertices[20].mPosition = { 1.0, -1.0, 1.0 };
    mVertices[21].mPosition = { 1.0, -1.0, -1.0 }; 
    mVertices[22].mPosition = { 1.0, 1.0, -1.0 };
    mVertices[23].mPosition = { 1.0, 1.0, 1.0 };

    for (auto& i : mVertices)
        i.mColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    for (size_t i = 0; i < 24; i += 4)
    {
        mVertices[i].mUV = { 0.0f, 0.0f };
        mVertices[i + 1].mUV = { 1.0f, 0.0f };
        mVertices[i + 2].mUV = { 1.0f, 1.0f };
        mVertices[i + 3].mUV = { 0.0f, 1.0f };
    }

    mIndices =
    {
        // front
        0,  1,  2,
        2,  3,  0,
        // top
        4,  5,  6,
        6,  7,  4,
        // back
        8,  9, 10,
        10, 11,  8,
        // bottom
        12, 13, 14,
        14, 15, 12,
        // left
        16, 17, 18,
        18, 19, 16,
        // right
        20, 21, 22,
        22, 23, 20
    };

    ComputeNormals();
}
