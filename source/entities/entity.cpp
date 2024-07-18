#include "entity.h"
#include "../game/state.h"

local G_State* state;

void E_Entity::Draw()
{
  state = G_State::Get();

  this->texture->Use();
  this->shader->Use();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->pos);
  model = glm::rotate(model, this->rot.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, this->rot.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, this->rot.z, glm::vec3(0, 0, 1));

  this->shader->SetUniform("uTexture", 0);
  this->shader->SetUniform("uModel", glm::value_ptr(model));
  this->shader->SetUniform("uProjection", glm::value_ptr(state->camera.ProjectionMatrix()));
  this->shader->SetUniform("uView", glm::value_ptr(state->camera.ViewMatrix()));

  this->mesh->Draw();
}