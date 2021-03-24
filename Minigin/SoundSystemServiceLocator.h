#pragma once
#include "SoundSystem.h"

class SoundSystemServiceLocator final
{
public:
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* pSoundSystem);
	static void ReleaseServiceLocator();
private:
	static SoundSystem* pSoundSystemInstance;
	static NullSoundSystem* pDefaultSoundSystemInstance;
};



