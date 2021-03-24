#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class Observer;
	class SubjectComponent;
	class ScoreComponent final : public ObjectComponent
	{
	public:
		ScoreComponent(GameObject* parent);
		~ScoreComponent();
		void IncreaseScore(int scoreIncrease);
		void AddObserver(Observer* observer);
	private:
		int m_CurrentScore;
		SubjectComponent* m_pSubject = nullptr;
	};
};
