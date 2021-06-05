#pragma once
#include "Component.h"

namespace Horizon
{
	class Observer;
	class SubjectComponent;
	class ScoreComponent final : public Component
	{
	public:
		ScoreComponent(GameObject* parent);
		~ScoreComponent();
		void IncreaseScore(int scoreIncrease);
		int GetScore() const;
		void AddObserver(Observer* observer);
	private:
		int m_CurrentScore;
		SubjectComponent* m_pSubject = nullptr;
	};
};
