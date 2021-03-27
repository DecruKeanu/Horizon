#include "MiniginPCH.h"
#include "SoundSystemServiceLocator.h"

SoundSystem* SoundSystemServiceLocator::pSoundSystemInstance = nullptr;
NullSoundSystem* SoundSystemServiceLocator::pDefaultSoundSystemInstance = nullptr;
std::vector<SoundSystem*> SoundSystemServiceLocator::systemsToDelete = {};

void SoundSystemServiceLocator::ReleaseServiceLocator()
{
	SafeDelete(pSoundSystemInstance);
	SafeDelete(pDefaultSoundSystemInstance);

	for (SoundSystem* pSoundSystem : systemsToDelete)
		SafeDelete(pSoundSystem);
}

SoundSystem& SoundSystemServiceLocator::GetSoundSystem()
{
	return *pSoundSystemInstance;
}

void SoundSystemServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
{
	if (pSoundSystem == nullptr)
	{
		pSoundSystemInstance = pDefaultSoundSystemInstance;
	}
	else
	{
		if (pSoundSystemInstance)
			systemsToDelete.push_back(std::forward<SoundSystem*>(std::move(pSoundSystemInstance)));

		pSoundSystemInstance = pSoundSystem;
	}

	//pSoundSystemInstance = (pSoundSystem == nullptr) ? pDefaultSoundSystemInstance : pSoundSystem;
}