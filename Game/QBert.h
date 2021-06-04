#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
	class ScoreComponent;
	class HealthComponent;
}

class QBert final
{
public:
	QBert(const rapidjson::Value& jsonObject);
	Horizon::GameObject* GetGameObject() const;
private:
	void Initialize();
	void InitializeHealthDisplay(Horizon::HealthComponent* const pQbertHealth);

	const rapidjson::Value& m_Value;
	Horizon::GameObject* m_pGameObject;
};

