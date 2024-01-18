#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	// Inherited via Scene
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	int framesCounter = 0;
};

