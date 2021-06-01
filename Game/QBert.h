#pragma once
#include "document.h"

class QBertMovementComponent;

namespace Horizon
{
	class GameObject;
}

class QBert final
{
public:
	QBert(const rapidjson::Value& jsonObject);
	Horizon::GameObject* GetGameObject() const;
private:
	void Initialize();

	const rapidjson::Value& m_Value;

	Horizon::GameObject* m_pGameObject;
};

