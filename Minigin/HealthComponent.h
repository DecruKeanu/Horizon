#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class Observer;
	class SubjectComponent;
	class HealthComponent final : public ObjectComponent
	{
	public:
		HealthComponent(GameObject* parent);
		HealthComponent(GameObject* parent, int lives);
		~HealthComponent();
		void DecreaseLive();
		void AddObserver(Observer* observer);
		int GetCurrentLives() const;
	private:
		int m_CurrentLives;
		SubjectComponent* m_pSubject = nullptr;
	};
}