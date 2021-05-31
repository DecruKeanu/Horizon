#pragma once
#include "Observer.h"

namespace Horizon
{
	class SubjectComponent final
	{
	public:
		SubjectComponent() = default;
		~SubjectComponent();
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const Event& event);
	private:
		std::vector<Observer*> m_Observers{nullptr };
	};
}
