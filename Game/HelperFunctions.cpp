#include "GamePCH.h"
#include "HelperFunctions.h"
#include <TransformComponent.h>

bool HelperFunctions::MoveToLerpedPos(const Horizon::IPoint2& originalPoint, const Horizon::IPoint2& desiredPoint, float lerpValue, Horizon::TransformComponent* pTransformComponent)
{
	lerpValue = std::min(lerpValue, 1.f);
	const Horizon::IPoint2 currentPoint = Horizon::MathHelper::IPoint2Lerp(originalPoint, desiredPoint, lerpValue);

	pTransformComponent->SetPosition(currentPoint);

	return (currentPoint.x == desiredPoint.x && currentPoint.y == desiredPoint.y);
}
