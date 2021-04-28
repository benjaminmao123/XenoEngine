#include "pch.h"
#include "Mesh.h"
#include "Core/Assert.h"

Xeno::Mesh::Mesh(const uint32_t topology) :
    mTopology(topology)
{ }

glm::vec3 Xeno::Mesh::ComputeNormal(const size_t index)
{
    XN_CORE_ASSERT(mIndices.size() >= 3 && index <= mIndices.size() - 3 &&
                   mVertices.size() >= 3);

    uint32_t i0 = mIndices[index];
    uint32_t i1 = mIndices[index + 1];
    uint32_t i2 = mIndices[index + 2];

    const glm::vec3& v0 = mVertices[i0].mPosition;
    const glm::vec3& v1 = mVertices[i1].mPosition;
    const glm::vec3& v2 = mVertices[i2].mPosition;

    glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

    return normal;
}

void Xeno::Mesh::ComputeNormals()
{
    for (size_t i = 0; i < mIndices.size(); i += 3)
    {
        uint32_t i0 = mIndices[i];
        uint32_t i1 = mIndices[i + 1];
        uint32_t i2 = mIndices[i + 2];

        mVertices[i0].mNormal += ComputeNormal(i);
        mVertices[i1].mNormal += ComputeNormal(i);
        mVertices[i2].mNormal += ComputeNormal(i);
    }

    for (auto& v : mVertices)
        v.mNormal = glm::normalize(v.mNormal);
}
