#include "SceneManager.h"

#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"

extern int screenWidth;
extern int screenHeight;

SceneManager* SceneManager::Get()
{
	static SceneManager sInstance;
	return &sInstance;
}

SceneManager::SceneManager()
{
	//std::unique_ptr<Scene> temp = std::make_unique<LogoScene>();
	mScenes.emplace_back(std::make_unique<LogoScene>());
	mScenes.emplace_back(std::make_unique<TitleScene>());
	mScenes.emplace_back(std::make_unique<GameScene>());

	int index = static_cast<int>(CurrentScene::LOGO);
	mCurrentScene = mScenes[index].get();
}

void SceneManager::Update()
{
	mCurrentScene->Update();
}

void SceneManager::Draw()
{
	mCurrentScene->Draw();
}

void SceneManager::ChangeScene(CurrentScene newScene)
{
	mCurrentScene->Exit();
	int index = static_cast<int>(newScene);
	mCurrentScene = mScenes[index].get();
	mCurrentScene->Enter();
}

void SceneManager::CloseScenes()
{
	mCurrentScene->Exit();
}
