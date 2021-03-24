#pragma once
#include "GameObject.h"
#include "Events.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer();
		virtual void OnNotify( const Event& event) = 0;
	};
}