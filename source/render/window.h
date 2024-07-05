#pragma once

#include "../base/base_inc.h"

struct R_Window
{
	I32 width, height;
  std::string title;
	B8 fullscreen;
	B8 running;
	SDL_Window *window;
	B8 vsync;

  void Create();
  U32 WindowFlags();
	void SwitchFullscreen();
};