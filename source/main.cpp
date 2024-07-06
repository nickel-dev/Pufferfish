#include "base/base_inc.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/window.h"
#include "game/state.h"

local G_State state;

function void KeyPressCallback(U8 keycode)
{
	switch (keycode)
	{
	case SDL_SCANCODE_F11:
		state.window.SwitchFullscreen();
		break;

	default:
		state.keyboard[keycode] = true;
		break;
	}
}

function void KeyReleaseCallback(U8 keycode)
{
	switch (keycode)
	{
	default:
		state.keyboard[keycode] = false;
		break;
	}
}

int main(int argc, char **argv)
{
	state.window = R_Window{
		.width = 1280,
		.height = 720,
		.title = "Pufferfish Sandbox", 
		.fullscreen = false,
		.running = true,
		.vsync = false
	};

	state.window.Create();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (state.window.running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				KeyPressCallback(e.key.keysym.scancode);
				break;

			case SDL_KEYUP:
				KeyReleaseCallback(e.key.keysym.scancode);
				break;

			case SDL_QUIT:
				state.window.running = false;
				break;

			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(state.window.window, &state.window.width, &state.window.height);
				break;

			default:
				break;
			}
		}

		state.time.Update();
		state.window.Update();

		SDL_SetWindowTitle(state.window.window, (state.window.title + " | FPS: " + std::to_string(state.time.frameTime)).c_str());
	}

	SDL_Quit();
	return 0;
}