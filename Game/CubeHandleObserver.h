#pragma once
#include <Observer.h>

class CubeHandleComponent;

class CubeHandleObserver final : public Horizon::Observer
{
public: 
	CubeHandleObserver(CubeHandleComponent* pCubeHandleComponent);
	void OnNotify(const Horizon::Event& event) override;

private:
	CubeHandleComponent* m_pCubeHandleComponent;
};

