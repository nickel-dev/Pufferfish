#include "state.h"

local G_State state;

// G_Time
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

// G_State
G_State* G_State::Get()
{
  return &state;
}

void G_State::AddEntity(E_Entity* entity)
{
  entity->id = this->entities.size();
  this->entities[entity->id] = entity;
}

E_Entity* G_State::NewEntity(E_Entity entity)
{
  E_Entity* e = (E_Entity*)calloc(1, sizeof(E_Entity));
  *e = entity;
  this->AddEntity(e);
  return e;
}