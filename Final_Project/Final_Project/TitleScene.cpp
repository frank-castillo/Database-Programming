#include "TitleScene.h"
#include "SceneManager.h"
#include "raylib.h"

extern int screenWidth;
extern int screenHeight;

void TitleScene::Enter()
{
}

void TitleScene::Exit()
{
	framesCounter = 0;
}

void TitleScene::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		SceneManager::Get()->ChangeScene(CurrentScene::GAMEPLAY);
	}
}

void TitleScene::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
	DrawText("VGP320_2042805_FinalProject ", 20, 20, 40, DARKGREEN);
	DrawText("PRESS ENTER TO OPEN VISUALIZER", 120, 220, 20, DARKGREEN);
}
