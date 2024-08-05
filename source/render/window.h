#ifndef __RENDER_WINDOW_H_
#define __RENDER_WINDOW_H_

#include "../base/base_inc.h"

struct R_Window
{
	I32 width, height;
	std::string title;
	B8 fullscreen, running, resizable, vsync, showFPS, centerMouse;
	SDL_Window *window;

	~R_Window();
	void Create();
	U32 WindowFlags();
	void SwitchFullscreen();
	void CheckEvents();
	void Update();
};

#endif