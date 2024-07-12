#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

#include "../base/base_inc.h"
#include "../render/window.h"
#include "../render/camera.h"
#include "../sound/sound.h"
#include "../input/controller.h"
#include "../input/keyboard.h"
#include "../entities/entity.h"

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
	I_Controller controller;
	I_Keyboard keyboard;
	std::vector<E_Entity*> entities;

	function G_State* Get();
};

#endif