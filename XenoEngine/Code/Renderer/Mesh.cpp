#include "pch.h"
#include "Renderer/Mesh.h"

Xeno::Mesh::Mesh(const Topology topology) :
    mTopology(topology)
{ }

Xeno::Mesh::~Mesh() = default;

Xeno::Mesh::Topology Xeno::Mesh::GetTopology() const
{
    return mTopology;
}
