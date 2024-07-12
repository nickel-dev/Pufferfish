#ifndef __INPUT_CONTROLLER_H_
#define __INPUT_CONTROLLER_H_

#include "../base/base_inc.h"

struct I_Controller
{
    SDL_GameController* controller = nullptr;
    B8 buttons[SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_MAX] = { false };

    void FindController();
    void Connect(I32 i);
    void Disconnect(I32 i);

    B8 CorrectController(I32 i);

    void ButtonPressCallback(U8 button);
    void ButtonReleaseCallback(U8 button);
};

#endif