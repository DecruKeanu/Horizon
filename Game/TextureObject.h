#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
}

class TextureObject final
{
public:
	TextureObject(const rapidjson::Value& jsonObject);
	Horizon::GameObject* GetGameObject() const;
private:
	void Initialize();

	const rapidjson::Value& m_Value;
	Horizon::GameObject* m_pGameObject = nullptr;
};
