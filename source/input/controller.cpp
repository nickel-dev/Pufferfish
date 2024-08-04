#include "controller.h"
#include "../game/state.h"

void I_Controller::FindController()
{
  for (U64 i = 0; i < SDL_NumJoysticks(); ++i)
    if (SDL_IsGameController(i))
      controller = SDL_GameControllerOpen(i);
}

void I_Controller::Connect(I32 i)
{
  if (controller)
    return;
  controller = SDL_GameControllerOpen(i);
}

void I_Controller::Disconnect(I32 i)
{
  if (CorrectController(i))
  {
    SDL_GameControllerClose(controller);
    FindController();
  }
}

B8 I_Controller::CorrectController(I32 i)
{
  return (controller && i == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)));
}

void I_Controller::ButtonPressCallback(U8 button)
{
  G_State* state = G_State::Get();

  switch (button)
  {
    case SDL_CONTROLLER_BUTTON_START:
      state->window.SwitchFullscreen();
      break;

    default:
      buttons[button] = true;
      break;
  }
}

void I_Controller::ButtonReleaseCallback(U8 button)
{
  G_State* state = G_State::Get();

  switch (button)
  {
    default:
      buttons[button] = false;
      break;
  }
}

void I_Controller::GetStickAxes()
{
	this->leftStick.x = (F32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / (F32)INT16_MAX;
	this->leftStick.y = (F32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / (F32)INT16_MAX;

	this->rightStick.x = (F32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) / (F32)INT16_MAX;
	this->rightStick.y = (F32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) / (F32)INT16_MAX;
}

void I_Controller::Clamp(F32 value)
{
  // X
  if (!(this->rightStick.x < -value) && !(this->rightStick.x > value))
    this->rightStick.x = null;
  if (!(this->leftStick.x < -value) && !(this->leftStick.x > value))
    this->leftStick.x = null;

  // Y
  if (!(this->rightStick.y < -value) && !(this->rightStick.y > value))
    this->rightStick.y = null;
  if (!(this->leftStick.y < -value) && !(this->leftStick.y > value))
    this->leftStick.y = null;
}