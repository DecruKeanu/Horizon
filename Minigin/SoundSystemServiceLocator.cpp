#include "MiniginPCH.h"
#include "SoundSystemServiceLocator.h"

SoundSystem* SoundSystemServiceLocator::pSoundSystemInstance = nullptr;
NullSoundSystem* SoundSystemServiceLocator::pDefaultSoundSystemInstance = nullptr;

void SoundSystemServiceLocator::ReleaseServiceLocator()
{
	SafeDelete<SoundSystem>(pSoundSystemInstance);
	SafeDelete<SoundSystem>(pDefaultSoundSystemInstance);
}

SoundSystem& SoundSystemServiceLocator::GetSoundSystem()
{
	return *pSoundSystemInstance;
}

void SoundSystemServiceLocator::RegisterSoundSystem(SoundSystem* pSoundSystem)
{
	pSoundSystemInstance = (pSoundSystem == nullptr) ? pDefaultSoundSystemInstance : pSoundSystem;
}