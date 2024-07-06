#include "base/base_inc.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/window.h"

local I32 frameCount;
local U64 lastTime, lastFrameTime;
local F32 deltaTime;
local B8 keyboard[256] = { false };

local R_Window window;

function void KeyPressCallback(U8 keycode)
{
	switch (keycode)
	{
	case SDL_SCANCODE_F11:
		window.SwitchFullscreen();
		break;

	default:
		keyboard[keycode] = true;
		break;
	}
}

function void KeyReleaseCallback(U8 keycode)
{
	switch (keycode)
	{
	default:
		keyboard[keycode] = false;
		break;
	}
}

int main(int argc, char **argv)
{
	window = R_Window{
		.width = 1280,
		.height = 720,
		.fullscreen = false,
		.running = true,
		.vsync = true
	};

	window.Create();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (window.running)
	{
		{
			U64 currentTime = SDL_GetTicks64();
			deltaTime = (F32)(currentTime - lastTime) / 1000.0f;
			lastTime = currentTime;

			if (lastFrameTime < time(0))
			{
				SDL_SetWindowTitle(window.window, (std::to_string(frameCount) + " FPS - Dungeons").c_str());
				frameCount = 0;
				lastFrameTime = time(0);
			}
			++frameCount;
		}

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
				window.running = false;
				break;

			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(window.window, &window.width, &window.height);
				break;

			default:
				break;
			}
		}

		// Render init
		SDL_GL_SwapWindow(window.window);

		glViewport(0, 0, window.width, window.height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT/* | GL_STENCIL_BUFFER_BIT*/ | GL_DEPTH_BUFFER_BIT);
	}

	// Deinitialize
	SDL_Quit();

	return 0;
}