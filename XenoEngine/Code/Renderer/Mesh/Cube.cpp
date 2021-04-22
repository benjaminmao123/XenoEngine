#include "pch.h"
#include "Cube.h"

Xeno::Cube::Cube(const uint32_t topology) :
    Mesh(topology)
{
    Vertex vertex[24];

    vertex[0].mPosition = { -1.0, -1.0, 1.0 };
    vertex[1].mPosition = { 1.0, -1.0, 1.0 };
    vertex[2].mPosition = { 1.0, 1.0, 1.0 };
    vertex[3].mPosition = { -1.0, 1.0, 1.0 };
    vertex[4].mPosition = { -1.0, 1.0, 1.0 };
    vertex[5].mPosition = { 1.0, 1.0, 1.0 };
    vertex[6].mPosition = { 1.0, 1.0, -1.0 };
    vertex[7].mPosition = { -1.0, 1.0, -1.0 };
    vertex[8].mPosition = { 1.0, -1.0, -1.0 };
    vertex[9].mPosition = { -1.0, -1.0, -1.0 };
    vertex[10].mPosition = { -1.0, 1.0, -1.0 };
    vertex[11].mPosition = { 1.0, 1.0, -1.0 };
    vertex[12].mPosition = { -1.0, -1.0, -1.0 };
    vertex[13].mPosition = { 1.0, -1.0, -1.0 };
    vertex[14].mPosition = { 1.0, -1.0, 1.0 };
    vertex[15].mPosition = { -1.0, -1.0, 1.0 };
    vertex[16].mPosition = { -1.0, -1.0, -1.0 };
    vertex[17].mPosition = { -1.0, -1.0, 1.0 };
    vertex[18].mPosition = { -1.0, 1.0, 1.0 };
    vertex[19].mPosition = { -1.0, 1.0, -1.0 };
    vertex[20].mPosition = { 1.0, -1.0, 1.0 };
    vertex[21].mPosition = { 1.0, -1.0, -1.0 }; 
    vertex[22].mPosition = { 1.0, 1.0, -1.0 };
    vertex[23].mPosition = { 1.0, 1.0, 1.0 };

    for (auto& i : vertex)
        i.mColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    for (int i = 0; i < 24; i += 4)
    {
        vertex[i].mUV = { 0.0f, 0.0f };
        vertex[i + 1].mUV = { 1.0f, 0.0f };
        vertex[i + 2].mUV = { 1.0f, 1.0f };
        vertex[i + 3].mUV = { 0.0f, 1.0f };
    }

    for (const auto& i : vertex)
        mVertices.emplace_back(i);

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
}
