#pragma once
#include "Component.h"
#include "Structs.h"
#include <array>
#include <functional>

//Credit to Elise Briers

namespace Horizon
{
	class GameObject;
	class TransformComponent;

	class TriggerComponent : public Horizon::Component
	{
	private:
		struct OverlapData
		{
			GameObject* pOverlapObject;
			bool IsOverlapping;
		};
	public:
		enum class TriggerAction
		{
			Enter,
			Exit
		};

		using CallBackFunction = std::function<void(GameObject*, GameObject*, TriggerAction)>;

		TriggerComponent(GameObject* pParent, const Horizon::IRect& collisionRect);
		void SetOnTriggerCallBack(const CallBackFunction& function);
		void OverlapsWith(GameObject* pGameObject);

		const Horizon::IRect& GetCollisionRect() const;
		const size_t GetOverlappingActorsSize();
	private:
		void Initialize() override;
		void Update() override;
		void Render() const override;
		Horizon::IRect m_CollisionRect;
		int m_OffsetX;
		int m_OffsetY;
		CallBackFunction m_CallBackFunction;
		std::vector<OverlapData> m_pOverlappingActors;
		Horizon::TransformComponent* m_pTransformComponent = nullptr;;
		
	};
}



