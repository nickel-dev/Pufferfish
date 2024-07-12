#ifndef __SOUND_SOUND_H_
#define __SOUND_SOUND_H_

#include "../base/base_inc.h"

struct S_Sound
{
    ma_sound* source;

    void Start();
    void Stop();
    
    B8 Playing();
    
    F32 GetVolume();
    void SetVolume(F32 volume);
};

struct S_SoundEngine
{
    ma_result result;
    ma_engine engine;

    void Create();
    S_Sound Load(const char* path);
};

#endif