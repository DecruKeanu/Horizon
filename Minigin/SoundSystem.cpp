#include "MiniginPCH.h"
#include "SoundSystem.h"

void SoundSystem::AddAudio(const char* audioPath)
{
	Mix_Chunk* sound = NULL;
	sound = Mix_LoadWAV(audioPath);
	m_pAudioVector.push_back(sound);
}


