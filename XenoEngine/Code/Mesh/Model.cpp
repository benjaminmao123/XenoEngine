#include "pch.h"
#include "Model.h"
#include "Core/Logger.h"
#include "Core/Assert.h"
#include "Resource/ResourceManager.h"

#include <assimp/postprocess.h>

Xeno::Model::Model(std::string const& path, const bool gamma) :
    mGammaCorrection(gamma)
{
    LoadModel(path);
}

void Xeno::Model::LoadModel(std::string const& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, 
                                             aiProcess_Triangulate | 
                                             aiProcess_GenSmoothNormals | 
                                             aiProcess_FlipUVs |
                                             aiProcess_CalcTangentSpace);

    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        XN_CORE_ERROR(importer.GetErrorString());

        return;
    }

    // retrieve the directory path of the filepath
    mDirectory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene);
}

void Xeno::Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (uint32_t i = 0; i < node->mNumMeshes; ++i)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        mMeshes.emplace_back(ProcessMesh(mesh, scene));
        ProcessMaterial(mesh, scene);
    }

    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (uint32_t i = 0; i < node->mNumChildren; ++i)
        ProcessNode(node->mChildren[i], scene);
}

Xeno::Mesh Xeno::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Mesh::Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture*> textures;

    // walk through each of the mesh's vertices
    for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Mesh::Vertex vertex;

        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.mPosition = vector;

        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.mNormal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;

            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.mUV = vec;

            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.mTangent = vector;

            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.mBitangent = vector;
        }
        else
            vertex.mUV = glm::vec2(0.0f, 0.0f);

        vertices.emplace_back(vertex);
    }

    // now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];

        // retrieve all indices of the face and store them in the indices vector
        for (uint32_t j = 0; j < face.mNumIndices; ++j)
            indices.emplace_back(face.mIndices[j]);
    }

    // return a mesh object created from the extracted mesh data
    //return Mesh(vertices, indices);
    return Mesh(GL_TRIANGLES, vertices, indices);
}

void Xeno::Model::ProcessMaterial(aiMesh* mesh, const aiScene* scene)
{
    // process materials
    aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];

    if (aiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString path;
        aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &path);

        Texture::TextureProperties props = { path.C_Str() };

        if (ResourceManager::AddTexture(std::make_shared<Texture>(props, true)))
            mTextures[Material::TextureMap::DIFFUSE] = ResourceManager::GetTexture(path.C_Str());
    }

    if (aiMat->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString path;
        aiMat->GetTexture(aiTextureType_SPECULAR, 0, &path);

        Texture::TextureProperties props = { path.C_Str() };

        if (ResourceManager::AddTexture(std::make_shared<Texture>(props, true)))
            mTextures[Material::TextureMap::SPECULAR] = ResourceManager::GetTexture(path.C_Str());
    }

    if (aiMat->GetTextureCount(aiTextureType_HEIGHT) > 0)
    {
        aiString path;
        aiMat->GetTexture(aiTextureType_HEIGHT, 0, &path);

        Texture::TextureProperties props = { path.C_Str() };

        if (ResourceManager::AddTexture(std::make_shared<Texture>(props, true)))
            mTextures[Material::TextureMap::NORMAL] = ResourceManager::GetTexture(path.C_Str());
    }

    if (aiMat->GetTextureCount(aiTextureType_AMBIENT) > 0)
    {
        aiString path;
        aiMat->GetTexture(aiTextureType_AMBIENT, 0, &path);

        Texture::TextureProperties props = { path.C_Str() };

        if (ResourceManager::AddTexture(std::make_shared<Texture>(props, true)))
            mTextures[Material::TextureMap::HEIGHT] = ResourceManager::GetTexture(path.C_Str());
    }

    if (aiMat->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString path;
        aiMat->GetTexture(aiTextureType_SPECULAR, 0, &path);

        Texture::TextureProperties props = { path.C_Str() };

        if (ResourceManager::AddTexture(std::make_shared<Texture>(props, true)))
            mTextures[Material::TextureMap::SPECULAR] = ResourceManager::GetTexture(path.C_Str());
    }
}
