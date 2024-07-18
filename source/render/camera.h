#ifndef __RENDER_CAMERA_H_
#define __RENDER_CAMERA_H_

#include "../base/base_inc.h"

struct R_Camera
{
  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
  glm::vec3 up = glm::vec3(0.0f, -1.0f, 0.0f);
  glm::vec3 dir = glm::normalize(pos + front);

  glm::mat4 ProjectionMatrix();
  glm::mat4 ViewMatrix();
};

#endif