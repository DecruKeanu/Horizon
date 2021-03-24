#pragma once
#include "SoundSystem.h"

class SDLSoundSystem final : public SoundSystem
{
public:
	void Play(SoundId id, int volume)  override;
	void Update() override;
};