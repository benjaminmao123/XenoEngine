#pragma once

#include "Core/Core.h"
#include "Mesh/Mesh.h"
#include "Graphics/Texture.h"
#include "Material/Material.h"

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <vector>
#include <unordered_map>

namespace Xeno
{
    class XENO_API Model
    {
    public:
        Model(std::string const& path, bool gamma = false);

    private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void LoadModel(std::string const& path);
        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        void ProcessMaterial(aiMesh* mesh, const aiScene* scene);

        std::unordered_map<Material::TextureMap, Texture*> mTextures;
        std::vector<Mesh> mMeshes;
        std::string mDirectory;
        bool mGammaCorrection;
    };
}