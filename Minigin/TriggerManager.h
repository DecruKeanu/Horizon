#pragma once
#include "Singleton.h"

namespace Horizon
{
	class TriggerComponent;

	class TriggerManager final : public Singleton<TriggerManager>
	{
	public:
		void AddTriggerComponent(TriggerComponent* pTriggerComponent);
		void ClearTriggerComponents();
		void Update();

		size_t GetTriggersSize();
	private:
		std::vector<TriggerComponent*> m_pTriggerComponents;
	};

}


