#pragma once
#include "SoundSystem.h"

namespace Horizon
{
	class SoundSystemServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(SoundSystem* pSoundSystem);
		static void ReleaseServiceLocator();
	private:
		static SoundSystem* pSoundSystemInstance;
		static NullSoundSystem* pDefaultSoundSystemInstance;
		static std::vector<SoundSystem*> systemsToDelete;
	};
}




