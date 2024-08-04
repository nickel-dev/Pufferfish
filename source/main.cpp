#include "base/base_inc.h"
#include "base/base_tools.h"
#include "entities/entity.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/texture.h"
#include "render/window.h"
#include "game/state.h"
#include "sound/sound.h"
#include "ui/text.h"

local G_State* state;

int main(int argc, char** argv)
{
  state = G_State::Get();

  state->window = R_Window{
		.width = 1280,
		.height = 720,
		.title = "Pufferfish",
		.fullscreen = false,
		.running = true,
		.resizable = true,
		.vsync = false,
		.showFPS = true
  };

  state->window.Create();
  state->soundEngine.Create();
  state->controller.FindController();

  state->camera.pos.z = 0.0f;

  UI_Font testFont("fonts/arial.ttf", 48);
  R_Shader testFontShader("shaders/text.glsl");

  R_Shader shader("shaders/default.glsl");
  R_Texture texture("textures/terrain-textured.png");
  R_Mesh mesh({
    R_Vertex(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
    R_Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
    R_Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
    R_Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f))
  }, {
    0, 1, 3,
    1, 2, 3
  });

  E_Entity tester = E_Entity{
		.pos = glm::vec3(0.0f, 0.0f, 5.0f),
		.rot = glm::vec3(0.0f, 0.0f, 0.0f),
		.shader = &shader,
		.texture = &texture,
		.mesh = &mesh
  };

  state->AddEntity(&tester);

  F32 yaw = 90.0f, pitch = 0.0f;

  while (state->window.running)
  {
  	state->time.Update();
    state->controller.GetStickAxes();
    state->controller.Clamp(0.4f);
 		state->window.CheckEvents();
  	state->window.Update();

    glDepthMask(false);

    state->camera.pos += state->controller.leftStick.x * glm::normalize(glm::cross(state->camera.front, state->camera.up)) * state->time.deltaTime * 2.0f;
    state->camera.pos += -state->controller.leftStick.y * state->camera.front * state->time.deltaTime * 2.0f;

    yaw -= state->controller.rightStick.x * 50.0f * state->time.deltaTime;
    pitch += state->controller.rightStick.y * 50.0f * state->time.deltaTime;

    state->camera.dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.dir.y = sin(glm::radians(pitch));
    state->camera.dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.front = glm::normalize(state->camera.dir);

    //tester.rot.y += state->time.timeScale * state->time.deltaTime;

    for (U64 i = 0; i < state->entityCount; ++i)
    {
      E_Entity* entity = state->entities[i];
      entity->Draw();
    }

    glDepthMask(true);
    testFont.Draw(testFontShader, "This is sample text!", 0, 0, 1.0f, glm::vec3(1.0f, 0.0f, 1.0f));
  }

  return EXIT_SUCCESS;
}