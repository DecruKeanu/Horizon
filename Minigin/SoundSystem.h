#pragma once
#include <vector>
#include "Structs.h"

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(SoundId id, int volume) = 0;
	virtual void Update() = 0;
	virtual void AddAudio(const char* audioPath);
protected:
	std::vector<Mix_Chunk*> m_pAudioVector{};

	static constexpr int m_MaxMessages = 16;
	AudioData m_Progressing[m_MaxMessages]{};

	int m_Head{};
	int m_Tail{};
};


class NullSoundSystem final : public SoundSystem
{
public:
	void Play(SoundId id, int volume) override { id, volume; }
	void Update() override {}
};



