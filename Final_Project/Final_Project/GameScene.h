#pragma once

#include "raylib.h"
#include <iostream>
#include "sqlite3.h"

#include "Scene.h"
#include <string>

#define MAX_POSTPRO_SHADERS         12

typedef enum {
	FX_GRAYSCALE = 0,
	FX_POSTERIZATION,
	FX_DREAM_VISION,
	FX_PIXELIZER,
	FX_CROSS_HATCHING,
	FX_CROSS_STITCHING,
	FX_PREDATOR_VIEW,
	FX_SCANLINES,
	FX_FISHEYE,
	FX_SOBEL,
	FX_BLOOM,
	FX_BLUR,
	//FX_FXAA
} PostproShader;

static const char* postproShaderText[] = {
	"GRAYSCALE",
	"POSTERIZATION",
	"DREAM_VISION",
	"PIXELIZER",
	"CROSS_HATCHING",
	"CROSS_STITCHING",
	"PREDATOR_VIEW",
	"SCANLINES",
	"FISHEYE",
	"SOBEL",
	"BLOOM",
	"BLUR",
	//"FXAA"
};

class GameScene : public Scene
{
public:
	// Inherited via Scene
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void LoadSettings();
	void SaveSettings();

	// Raylib elements
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Model> mModel;
	std::unique_ptr<Texture2D> mTexture;
	std::unique_ptr<RenderTexture2D> mRenderTexture;
	std::unique_ptr<Sound> mFxButton;   // Load button sound
	std::unique_ptr<Texture2D> mButtonTexture; // Load button texture
	std::unique_ptr<Music> mMusic;

	Shader shaders[MAX_POSTPRO_SHADERS] = { 0 };
	Vector3 modelPosition;
	Vector2 mousePoint = { 0.0f, 0.0f };

	// Define button bounds on screen
	Rectangle btnBounds;

	// Define frame rectangle for drawing
	Rectangle sourceRec;
	float frameHeight;
	// ----------------------------------
	float masterVolume = 1.0f;
	float musicVolume = 1.0f;
	float sfxVolume = 1.0f;
	float musicLength = 0.0f;
	float timePlayed = 0.0f;

	int newScreenHeight = 0;
	int newScreenWidth = 0;
	int framesCounter = 0;
	int currentShader = FX_GRAYSCALE;
	int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED

	bool muteAudio = false;
	bool applyChanges = false;
	bool btnAction = false;         // Button action should be activated
	bool wasDatabaseLoaded = false;

	// Database
	sqlite3* db;
	char* gError = 0;
	std::string sqlQuery;
	std::string tableName;
};

