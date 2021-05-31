#pragma once
#include "Observer.h"

namespace Horizon
{
    class HealthDisplayComponent;
    class HealthDisplayObserver final:  public Observer
    {
    public:
        HealthDisplayObserver(HealthDisplayComponent* healthDisplayComponent);
        void OnNotify( const Event& event) override;
    private:
        HealthDisplayComponent* m_pHealthDisplayComponent = nullptr;
    };
}

