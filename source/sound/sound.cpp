#define MINIAUDIO_IMPLEMENTATION
#include "sound.h"

// SoundEngine
void S_SoundEngine::Create()
{
	result = ma_engine_init(NULL, &engine);
	LOG_ASSERT((result == MA_SUCCESS), "Initializing audio engine failed! error: %d", result);
}

S_Sound S_SoundEngine::Load(const char* path)
{
	ma_sound* source = (ma_sound*)malloc(sizeof(ma_sound));
	ma_result result = ma_sound_init_from_file(&engine, path, 0, NULL, NULL, source);

	LOG_ASSERT((result == MA_SUCCESS), "Loading sound failed! filename: %s", path);

    S_Sound s;
    s.source = source;

    return s;
}

// Sound
void S_Sound::Start()
{
	ma_sound_start((ma_sound*)source);
}

void S_Sound::Stop()
{
	ma_sound_stop((ma_sound*)source);
}

B8 S_Sound::Playing()
{
	return !ma_sound_at_end((const ma_sound*)source);
}

F32 S_Sound::GetVolume()
{
	return ma_sound_get_volume(source);
}

void S_Sound::SetVolume(F32 volume)
{
	ma_sound_set_volume(source, volume);
}