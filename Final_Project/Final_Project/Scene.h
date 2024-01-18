#pragma once

#include "UtilEnums.h"

class Scene
{
public:
	virtual ~Scene() = default;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
