#pragma once
#include "Scene.h"

class LogoScene : public Scene
{
public:
	// Inherited via Scene
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int framesCounter = 0;
	int state = 0;
};

