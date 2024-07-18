#include "camera.h"
#include "../game/state.h"

local G_State* state;

glm::mat4 R_Camera::ProjectionMatrix()
{
  state = G_State::Get();
  return glm::perspective(glm::radians(60.0f), (F32)state->window.width / state->window.height, 0.1f, 1000.0f);
}

glm::mat4 R_Camera::ViewMatrix()
{
  return glm::lookAt(this->pos, this->pos + this->dir, this->up);
}