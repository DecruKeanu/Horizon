#pragma once
#include "Component.h"

namespace Horizon
{
	class Observer;
	class SubjectComponent;
	class HealthComponent final : public Component
	{
	public:
		HealthComponent(GameObject* parent);
		HealthComponent(GameObject* parent, int lives);
		~HealthComponent();
		void DecreaseLive();
		void AddObserver(Observer* observer);
		int GetCurrentLives() const;
		void SetCurrentLives(int currentLives);
	private:
		int m_CurrentLives;
		SubjectComponent* m_pSubject = nullptr;
	};
}
