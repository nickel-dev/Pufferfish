#ifndef __RENDER_MODEL_H_
#define __RENDER_MODEL_H_

#include "../base/base_inc.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

struct R_Model
{
  std::vector<R_Mesh> meshes;
  std::string directory;

  R_Model();
  R_Model(std::string path);
  void Load(std::string path);
  void ProcessNode(aiNode* node, const aiScene* scene);
  R_Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<R_Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType type);
  void Draw();
};

#endif