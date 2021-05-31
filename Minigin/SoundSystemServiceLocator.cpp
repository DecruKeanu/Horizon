#include "MiniginPCH.h"
#include "SoundSystemServiceLocator.h"

Horizon::SoundSystem* Horizon::SoundSystemServiceLocator::pSoundSystemInstance = nullptr;
Horizon::NullSoundSystem* Horizon::SoundSystemServiceLocator::pDefaultSoundSystemInstance = nullptr;
std::vector<Horizon::SoundSystem*> Horizon::SoundSystemServiceLocator::systemsToDelete = {};

void Horizon::SoundSystemServiceLocator::ReleaseServiceLocator()
{
	SafeDelete(pSoundSystemInstance);
	SafeDelete(pDefaultSoundSystemInstance);

	for (SoundSystem* pSoundSystem : systemsToDelete)
		SafeDelete(pSoundSystem);
}

Horizon::SoundSystem& Horizon::SoundSystemServiceLocator::GetSoundSystem()
{
	return *pSoundSystemInstance;
}

void Horizon::SoundSystemServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
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