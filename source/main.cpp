#include "base/base_inc.h"
#include "entities/entity.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/window.h"
#include "game/state.h"
#include "sound/sound.h"
#include <cstdlib>

local G_State* state;

int main(int argc, char **argv)
{
	state = G_State::Get();

	state->window = R_Window{
		.width = 1280,
		.height = 720,
		.title = "Pufferfish", 
		.fullscreen = false,
		.running = true,
		.vsync = false,
		.showFPS = true
	};

	state->window.Create();
	state->soundEngine.Create();
	state->controller.FindController();

	while (state->window.running)
	{
		state->window.CheckEvents();
		state->time.Update();
		state->window.Update();

		for (E_Entity* entity : state->entities)
		{
			entity->texture->Use();
			entity->shader->Use();
			entity->mesh->Draw();
		}
	}

	return EXIT_SUCCESS;
}