#pragma once
#include "Singleton.h"

namespace Horizon
{
	class TriggerComponent;

	class TriggerManager final : public Singleton<TriggerManager>
	{
	public:
		void AddTriggerComponent(TriggerComponent* pTriggerComponent);
		void Update();
	private:
		std::vector<TriggerComponent*> m_pTriggerComponents;
	};

}


