#pragma once
namespace Horizon
{
	class TransformComponent;
}

namespace HelperFunctions
{
	bool MoveToLerpedPos(const Horizon::IPoint2& originalPoint, const Horizon::IPoint2& desiredPoint, float lerpValue, Horizon::TransformComponent* pTransformComponent);
	//bool HopToLerpedPos(const Horizon::IPoint2& originalPoint, const Horizon::IPoint2& desiredPoint, float lerpValue, float hopHeight, Horizon::TransformComponent* pTransformComponent);
}

