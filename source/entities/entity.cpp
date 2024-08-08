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
  modelMatrix = glm::translate(modelMatrix, this->pos);
  modelMatrix = glm::scale(modelMatrix, this->scale);
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.x), glm::vec3(1, 0, 0));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.y), glm::vec3(0, 1, 0));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rot.z), glm::vec3(0, 0, 1));

  this->shader->SetUniform("uModel", glm::value_ptr(modelMatrix));
  this->shader->SetUniform("uProjection", glm::value_ptr(state->camera.ProjectionMatrix()));
  this->shader->SetUniform("uView", glm::value_ptr(state->camera.ViewMatrix()));

  this->shader->SetUniform("light.pos", state->sunLight.pos);
  this->shader->SetUniform("light.dir", state->sunLight.dir);

  this->shader->SetUniform("light.ambient", state->sunLight.ambient);
  this->shader->SetUniform("light.diffuse", state->sunLight.diffuse);
  this->shader->SetUniform("light.specular", state->sunLight.specular);

  this->model.Draw();
}

E_Entity::~E_Entity()
{
  model.meshes.clear();
}