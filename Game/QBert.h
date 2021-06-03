#pragma once
#include "document.h"

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
	//void FeetTriggerCallBack(GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction, const std::string&);

	const rapidjson::Value& m_Value;
	Horizon::GameObject* m_pGameObject;
};

