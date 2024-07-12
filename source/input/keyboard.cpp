#include "keyboard.h"
#include "../game/state.h"

void I_Keyboard::KeyPressCallback(U8 scancode)
{
    G_State* state = G_State::Get();

    switch (scancode)
	{
	case SDL_SCANCODE_F11:
		state->window.SwitchFullscreen();
		break;

	default:
		keys[scancode] = true;
		break;
	}
}

void I_Keyboard::KeyReleaseCallback(U8 scancode)
{
    G_State* state = G_State::Get();
	
    switch (scancode)
	{
	default:
		keys[scancode] = false;
		break;
	}
}