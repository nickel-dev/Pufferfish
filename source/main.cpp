#include "base/base_inc.h"
#include "base/base_tools.h"
#include "entities/entity.h"
#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/texture.h"
#include "render/window.h"
#include "game/state.h"
#include "sound/sound.h"

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

  while (state->window.running)
  {
  	state->time.Update();
    state->controller.GetStickAxes();
    state->controller.FixStickDrift();
 		state->window.CheckEvents();
  	state->window.Update();

    state->camera.pos += glm::vec3(0.0f, 0.0f, state->controller.leftStick.y) * state->time.deltaTime;

    tester.rot.y += state->controller.rightStick.x * state->time.deltaTime;

		for (U64 i = 0; i < state->entityCount; ++i)
		{
			E_Entity* entity = state->entities[i];
			entity->Draw();
		}
  }

  return EXIT_SUCCESS;
}