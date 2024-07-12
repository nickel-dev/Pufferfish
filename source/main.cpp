#include "base/base_inc.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/window.h"
#include "game/state.h"
#include "sound/sound.h"

local G_State* state;

int main(int argc, char **argv)
{
	state = G_State::Get();

	state->window = R_Window{
		.width = 1600,
		.height = 900,
		.title = "Pufferfish Sandbox", 
		.fullscreen = false,
		.running = true,
		.vsync = false
	};

	state->window.Create();
	state->soundEngine.Create();

	state->controller.FindController();

	S_Sound sound = state->soundEngine.Load("sounds/Yuno Miles - Space Jam (Official Video) (Prod. AyeKeem).mp3");
	sound.Start();

	while (state->window.running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				state->keyboard.KeyPressCallback(e.key.keysym.scancode);
				break;

			case SDL_KEYUP:
				state->keyboard.KeyReleaseCallback(e.key.keysym.scancode);
				break;
			
			case SDL_CONTROLLERDEVICEADDED:
				state->controller.Connect(e.cdevice.which);
				break;
			
			case SDL_CONTROLLERDEVICEREMOVED:
				state->controller.Disconnect(e.cdevice.which);
				break;
			
			case SDL_CONTROLLERBUTTONDOWN:
				if (state->controller.CorrectController(e.cdevice.which))
					state->controller.ButtonPressCallback(e.cbutton.button);
				break;
			
			case SDL_CONTROLLERBUTTONUP:
				if (state->controller.CorrectController(e.cdevice.which))
					state->controller.ButtonReleaseCallback(e.cbutton.button);
				break;

			case SDL_QUIT:
				state->window.running = false;
				break;

			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(state->window.window, &state->window.width, &state->window.height);
				break;

			default:
				break;
			}
		}

		state->time.Update();
		state->window.Update();

		SDL_SetWindowTitle(state->window.window, (state->window.title + " | FPS: " + std::to_string(state->time.frameTime)).c_str());
	}

	SDL_Quit();
	return 0;
}