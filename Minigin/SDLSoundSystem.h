#pragma once
#include "SoundSystem.h"

namespace Horizon
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		void QueueEvent(SoundId id, int volume)  override;
		void Update() override;
	protected:

		static constexpr int m_MaxMessages = 16;
		AudioData m_Progressing[m_MaxMessages]{};

		int m_Head{};
		int m_Tail{};
	};
}
