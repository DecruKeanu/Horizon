#pragma once
#include "Prefab.h"
#include "document.h"

class QBertMovementComponent;

class QBert final : public dae::Prefab
{
public:
	QBert(const rapidjson::Value& jsonObject);
private:
	void Initialize();

	const rapidjson::Value& m_Value;
};

