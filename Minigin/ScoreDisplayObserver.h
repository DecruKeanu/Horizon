#pragma once
#include "Observer.h"

namespace dae
{
    class ScoreDisplayComponent;
    class ScoreDisplayObserver final: public Observer
    {
    public:
        ScoreDisplayObserver(ScoreDisplayComponent* scoreDisplayComponent);
        void OnNotify(const Event& event) override;
    private:
        ScoreDisplayComponent* m_pScoreDisplayComponent = nullptr;
    };
}