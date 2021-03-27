#pragma once
#include <vector>
#include "Structs.h"

class SoundSystem //SoundEvent
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(SoundId id, int volume) = 0; //QueueEvent
	virtual void Update() = 0; //ExecuteEvent
	virtual void AddAudio(const char* audioPath);
protected:
	std::vector<Mix_Chunk*> m_pAudioVector{}; //to inherited classes
};


class NullSoundSystem final : public SoundSystem
{
public:
	void Play(SoundId id, int volume) override { id, volume; }
	void Update() override {}
};



