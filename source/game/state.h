#pragma once

#include "../base/base_inc.h"
#include "../render/window.h"
#include "../render/camera.h"
#include "../sound/sound.h"

struct G_Time
{
	F32 deltaTime = 0.0f;
	F32 timeScale = 1.0f;
	U64 frameTime = 0;

	U64 _delta_lastTime;
	U64 _frameTime_lastTime;
	U64 _frameTime_counter;

	void Update();
};

struct G_State
{
	R_Window window;
	R_Camera camera;
	G_Time time;
	S_SoundEngine soundEngine;
	B8 keyboard[256] = { false };
};