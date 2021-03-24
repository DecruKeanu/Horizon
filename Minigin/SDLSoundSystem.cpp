#include "MiniginPCH.h"
#include "SDLSoundSystem.h"
#include <cassert>

void SDLSoundSystem::Play(SoundId id, int volume)
{
	for (int idx = m_Head; idx != m_Tail; idx = (idx + 1) % m_MaxMessages)
	{
		if (m_Progressing[idx].id == id)
		{
			m_Progressing[idx].volume = std::max(volume, m_Progressing[idx].volume);
			return;
		}
	}
	assert((m_Tail + 1) % m_MaxMessages != m_Head);

	m_Progressing[m_Tail].id = id;
	m_Progressing[m_Tail].volume = volume;
	m_Tail = (m_Tail + 1) % m_MaxMessages;
}

void SDLSoundSystem::Update()
{
	if (m_Head == m_Tail)
		return;

	if (Mix_Playing(-1) == 4) //look into mixAllocateChannel
		return;

	const SoundId id = m_Progressing[m_Head].id;
	const int volume = m_Progressing[m_Head].volume;

	Mix_VolumeChunk(m_pAudioVector[id], volume);
	Mix_PlayChannel(-1, m_pAudioVector[id], 0);

	m_Head = (m_Head + 1) % m_MaxMessages;
}