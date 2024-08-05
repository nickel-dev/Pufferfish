#include "base/base_inc.h"
#include "base/base_tools.h"
#include "entities/entity.h"
#include "glm/common.hpp"
#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/texture.h"
#include "render/window.h"
#include "render/model.h"
#include "game/state.h"
#include "sound/sound.h"
#include "ui/text.h"


local G_State* state;

/*static char* FormatString(const char* format, ...)
{
  va_list vl, vc;
  va_start(vl, format);
  va_copy(vc, vl);

  char* buffer = NULL;
  size_t s = snprintf(buffer, 0, format, vc) + 1;
  buffer = (char*)malloc(s);
  sprintf_s(buffer, s, format, vc);

  LOG(format, vc);
  LOG("\n");

  va_end(vc);
  va_end(vl);
  return buffer;
}*/
#if _MSVC_LANG == 202002L
#define STR_FORMAT( ...) std::format(__VA_ARGS__).c_str()
#else
#define STR_FORMAT(...) "null"
#endif

int main(int argc, char** argv)
{
  state = G_State::Get();

  state->window = R_Window{
		.width = 1600,
		.height = 900,
		.title = "Pufferfish",
		.fullscreen = false,
		.running = true,
		.resizable = true,
		.vsync = false,
		.showFPS = true,
    .centerMouse = false
  };

  state->window.Create();
  state->soundEngine.Create();
  state->controller.FindController();

  state->camera.pos.z = 0.0f;

  UI_Font font("fonts/Arial.ttf", 14);

  R_Shader defaultShader("shaders/default.glsl");
  R_Shader fontShader("shaders/text.glsl");

  E_Entity duck = {
		.pos = glm::vec3(0.0f, 0.0f, 5.0f),
		.rot = glm::vec3(180.0f, 0.0f, 0.0f),
		.scale = glm::vec3(0.01f, 0.01f, 0.01f),
		.shader = &defaultShader,
		.model = R_Model("models/Duck.gltf")
  };
  state->AddEntity(&duck);

  E_Entity cube = {
		.pos = glm::vec3(5.0f, 0.0f, 8.0f),
		.rot = glm::vec3(0.0f, 40.0f, 0.0f),
		.scale = glm::vec3(1.0f, 1.0f, 1.0f),
		.shader = &defaultShader,
		.model = R_Model("models/cube.gltf")
  };
  state->AddEntity(&cube);

  F32 yaw = 90.0f, pitch = 0.0f;

  while (state->window.running)
  {
  	state->time.Update();
    state->controller.GetStickAxes();
    state->controller.Clamp(0.2f);
 		state->window.CheckEvents();
  	state->window.Update();

    state->camera.pos += state->controller.leftStick.x * glm::normalize(glm::cross(state->camera.front, state->camera.up)) * state->time.deltaTime * 2.0f;
    state->camera.pos += -state->controller.leftStick.y * state->camera.front * state->time.deltaTime * 2.0f;

    yaw -= state->controller.rightStick.x * 150.0f * state->time.deltaTime;
    pitch += state->controller.rightStick.y * 150.0f * state->time.deltaTime;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    state->camera.dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.dir.y = sin(glm::radians(pitch));
    state->camera.dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.front = glm::normalize(state->camera.dir);

    for (U64 i = 0; i < state->entities.size(); ++i)
    {
      E_Entity* entity = state->entities[i];
      entity->Draw();
    }

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    font.Draw(fontShader, STR_FORMAT("FPS: {}", state->time.frameTime), 0 , 60, 1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    font.Draw(fontShader, STR_FORMAT("X: {}", state->camera.pos.x), 0, 40, 1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    font.Draw(fontShader, STR_FORMAT("Y: {}", state->camera.pos.y), 0, 20, 1.0f, glm::vec3(0.0f, 1.0f, 1.0f));
    font.Draw(fontShader, STR_FORMAT("Z: {}", state->camera.pos.z), 0, 0, 1.0f, glm::vec3(1.0f, 0.5f, 0.0f));

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
  }

  return EXIT_SUCCESS;
}