#include "entity.h"
#include "../game/state.h"

local G_State* state;

void E_Entity::Draw()
{
  if (!state)
    state = G_State::Get();
  if (this->shader)
    this->shader->Use();

  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(modelMatrix, this->scale);
  modelMatrix = glm::translate(modelMatrix, this->pos);
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.x), glm::vec3(1, 0, 0));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.y), glm::vec3(0, 1, 0));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.z), glm::vec3(0, 0, 1));

  this->shader->SetUniform("uTexture", 0);
  this->shader->SetUniform("uModel", glm::value_ptr(modelMatrix));
  this->shader->SetUniform("uProjection", glm::value_ptr(state->camera.ProjectionMatrix()));
  this->shader->SetUniform("uView", glm::value_ptr(state->camera.ViewMatrix()));

  this->model.Draw();

  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

E_Entity::~E_Entity()
{
  model.meshes.clear();
}