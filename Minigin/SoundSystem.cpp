#include "MiniginPCH.h"
#include "SoundSystem.h"

void Horizon::SoundSystem::AddAudio(const char* audioPath)
{
	Mix_Chunk* const sound = Mix_LoadWAV(audioPath);
	m_pAudioVector.push_back(sound);
}


