#include "model.h"
#include "assimp/postprocess.h"
#include "texture.h"

// Credits to https://learnopengl.com/Model-Loading/Model

R_Model::R_Model()
{
  return;
}

R_Model::R_Model(std::string path)
{
  this->Load(path);
}

void R_Model::Load(std::string path)
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes | aiProcess_GenNormals);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
      std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
      return;
  }

  this->directory = path.substr(0, path.find_last_of('/'));
  this->ProcessNode(scene->mRootNode, scene);
}

void R_Model::ProcessNode(aiNode* node, const aiScene* scene)
{
  for (U32 i = 0; i < node->mNumMeshes; ++i)
  {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(this->ProcessMesh(mesh, scene));
  }

  for(U32 i = 0; i < node->mNumChildren; ++i)
    this->ProcessNode(node->mChildren[i], scene);
}

R_Mesh R_Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
  std::vector<R_Vertex> vertices;
  std::vector<U32> indices;
  std::vector<R_Texture> textures;

  // Vertices
  for(unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
      R_Vertex vertex;
      glm::vec3 vector;

      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.pos = vector;

      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;

      if (mesh->mTextureCoords[0])
      {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.texCoord = vec;
      }
      else
        vertex.texCoord = glm::vec2(0.0f, 0.0f);

      vertices.push_back(vertex);
  }

  // Indices
  for(U32 i = 0; i < mesh->mNumFaces; ++i)
  {
    aiFace face = mesh->mFaces[i];
    for(U32 j = 0; j < face.mNumIndices; ++j)
      indices.push_back(face.mIndices[j]);
  }

  // Textures
  if(mesh->mMaterialIndex >= 0)
  {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    textures = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE);
  }

  R_Mesh m(vertices, textures, indices);
  m.Draw(); // For some reason it failes when I dont draw it here lmfao!

  return m;
}

std::vector<R_Texture> R_Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type)
{
  std::vector<R_Texture> textures;

  for(U32 i = 0; i < material->GetTextureCount(type); ++i)
  {
      aiString str;
      material->GetTexture(type, i, &str);

      R_Texture texture((directory + std::string("/") + str.C_Str()).c_str());
      textures.push_back(texture);
  }
  return textures;
}

void R_Model::Draw()
{
  for(U64 i = 0; i < this->meshes.size(); ++i)
    this->meshes[i].Draw();
}