#include "pch.h"
#include "Renderer/Mesh.h"

Xeno::Mesh::Mesh(const Topology topology) :
    mTopology(topology)
{ }

Xeno::Mesh::~Mesh()
{ }

Xeno::Mesh::Topology Xeno::Mesh::GetTopology() const
{
    return mTopology;
}