#pragma once

#include "Core/Core.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>

namespace Xeno::Utility
{
    template <typename T>
    class Graph
    {
    public:
        void AddVertex(const T& data)
        {
            mVertices.emplace_back(data);
        }

        void AddEdge(const uint32_t source, const uint32_t destination)
        {
            XN_ASSERT(source >= mVertices.size() || destination >= mVertices.size());

            mVertices[source].AddEdge(destination);
        }

    private:
        class Vertex
        {
        public:
            explicit Vertex(const T& data) :
                mData(data)
            { }

            void AddEdge(const uint32_t destination)
            {
                if (mUniqueEdges.find(destination) == mUniqueEdges.end())
                {
                    mEdges[mEdges.size()] = destination;
                    mUniqueEdges.insert(destination);
                }
            }

            int32_t GetEdge(const uint32_t index)
            {
                if (mEdges.find(index) != mEdges.end())
                    return mEdges[index];

                return -1;
            }

            T mData;

        private:
            std::unordered_map<uint32_t, int32_t> mEdges;
            std::unordered_set<int32_t> mUniqueEdges;
        };

        std::vector<Vertex> mVertices;
    };
}