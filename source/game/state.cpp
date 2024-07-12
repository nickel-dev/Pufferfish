#include "state.h"

local G_State state;

G_State* G_State::Get()
{
	return &state;
}

void G_Time::Update()
{
	U64 currentTime = SDL_GetTicks64();
	deltaTime = (F32)(currentTime - _delta_lastTime) / 1000.0f;
	_delta_lastTime = currentTime;
  
	if (_frameTime_lastTime < time(0))
	{
		frameTime = _frameTime_counter;
		_frameTime_counter = 0;
		_frameTime_lastTime = time(0);
	}
	++_frameTime_counter;
}