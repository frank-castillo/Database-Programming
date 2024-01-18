#pragma once

#include "Scene.h"
#include "UtilEnums.h"
#include <vector>
#include <iostream>

class SceneManager
{
public:
	static SceneManager* Get();

public:
	SceneManager();
	void Update();
	void Draw();
	void ChangeScene(CurrentScene newScene);
	void CloseScenes();

private:
	Scene* mCurrentScene = nullptr;
	std::vector<std::unique_ptr<Scene>> mScenes;
};

