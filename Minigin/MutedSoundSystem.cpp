#include "MiniginPCH.h"
#include "MutedSoundSystem.h"
#include <cassert>

void MutedSoundSystem::QueueEvent(SoundId id, int volume)
{
	assert((m_Tail + 1) % m_MaxMessages != m_Head);

	m_Progressing[m_Tail].id = id;
	m_Progressing[m_Tail].volume = volume;
	m_Tail = (m_Tail + 1) % m_MaxMessages;
}

void MutedSoundSystem::Update()
{
	if (m_Head == m_Tail)
		return;

	if (Mix_Playing(-1) == 4) //look into mixAllocateChannel
		return;

	const SoundId id = m_Progressing[m_Head].id;
	const int volume = m_Progressing[m_Head].volume;

	std::cout << "muted SoundSystem: sound with id " << id << " should be played with volume " << volume << std::endl;

	m_Head = (m_Head + 1) % m_MaxMessages;
}