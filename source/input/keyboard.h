#ifndef __INPUT_KEYBOARD_H_
#define __INPUT_KEYBOARD_H_

#include "../base/base_inc.h"

struct I_Keyboard
{
  B8 keys[256] = { false };

  void KeyPressCallback(U8 scancode);
  void KeyReleaseCallback(U8 scancode);
};

#endif