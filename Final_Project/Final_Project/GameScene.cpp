#include "GameScene.h"
#include "SceneManager.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 
#include <format>
#include <sstream>

extern int screenWidth;
extern int screenHeight;

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define NUM_FRAMES 3;

using std::string;

namespace
{
	int height, width, shader;
	float master, sfx, music;
	bool mute;

	int Callback(void* data, int argc, char** argv, char** azColName)
	{
		for (int row = 0; row < argc; row++)
		{
			std::cout << azColName[row] << " : " << argv[row] << " | ";
		}

		std::cout << std::endl;

		return 0;
	}

	int LoadCallback(void* data, int argc, char** argv, char** azColName)
	{
		for (int row = 0; row < argc; row++)
		{
			if (string(azColName[row]) == "Screen_Height")
			{
				std::stringstream str;
				int x;
				str << argv[row];
				str >> x;
				height = x;
				continue;
			}
			if (string(azColName[row]) == "Screen_Width")
			{
				std::stringstream str;
				int x;
				str << argv[row];
				str >> x;
				width = x;
				continue;
			}
			if (string(azColName[row]) == "Master_Volume")
			{
				master = atof(argv[row]);
				continue;
			}
			if (string(azColName[row]) == "SFX_Volume")
			{
				sfx = atof(argv[row]);
				continue;
			}
			if (string(azColName[row]) == "Music_Volume")
			{
				music = atof(argv[row]);
				continue;
			}
			if (string(azColName[row]) == "Shader")
			{
				std::stringstream str;
				int x;
				str << argv[row];
				str >> x;
				shader = x;
				continue;
			}
		}

		return 0;
	}
}

void GameScene::Enter()
{
	int sq = sqlite3_open("2042805_FinalAssignment.db", &db);

	if (sq == SQLITE_OK)
	{
		std::cout << "Database opened with success!\n\n";
	}
	else
	{
		std::cout << "Failure to open the database\n\n";
	}

	string selectQuery = "SELECT * FROM Configuration WHERE User_Profile = 1;";
	sqlite3_exec(db, selectQuery.c_str(), LoadCallback, NULL, NULL);
	
	if (!wasDatabaseLoaded)
	{
		LoadSettings();
	}

	InitAudioDevice();

	mMusic = std::make_unique<Music>(LoadMusicStream("resources/music.mp3"));
	musicLength = GetMusicTimeLength(*mMusic);

	PlayMusicStream(*mMusic);


	camera = std::make_unique<Camera>();
	camera->position = { 2.0f,3.0f,2.0f };
	camera->target = { 0.0f, 1.0f, 0.0f };
	camera->up = { 0.0f, 1.0f, 0.0f };
	camera->fovy = 45.0f;
	camera->projection = 0;

	mModel = std::make_unique<Model>();
	*mModel = LoadModel("./resources/models/church.obj");
	mTexture = std::make_unique<Texture2D>();
	*mTexture = LoadTexture("./resources/models/church_diffuse.png");
	mModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *mTexture;
	modelPosition = { 0.0f, 0.0f, 0.0f };

	// Load all postpro shaders
	// NOTE 1: All postpro shader use the base vertex shader (DEFAULT_VERTEX_SHADER)
	// NOTE 2: We load the correct shader depending on GLSL version
	// NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
	shaders[FX_GRAYSCALE] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/grayscale.fs", GLSL_VERSION));
	shaders[FX_POSTERIZATION] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/posterization.fs", GLSL_VERSION));
	shaders[FX_DREAM_VISION] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/dream_vision.fs", GLSL_VERSION));
	shaders[FX_PIXELIZER] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/pixelizer.fs", GLSL_VERSION));
	shaders[FX_CROSS_HATCHING] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/cross_hatching.fs", GLSL_VERSION));
	shaders[FX_CROSS_STITCHING] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/cross_stitching.fs", GLSL_VERSION));
	shaders[FX_PREDATOR_VIEW] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/predator.fs", GLSL_VERSION));
	shaders[FX_SCANLINES] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/scanlines.fs", GLSL_VERSION));
	shaders[FX_FISHEYE] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/fisheye.fs", GLSL_VERSION));
	shaders[FX_SOBEL] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/sobel.fs", GLSL_VERSION));
	shaders[FX_BLOOM] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/bloom.fs", GLSL_VERSION));
	shaders[FX_BLUR] = LoadShader(0, TextFormat("./resources/shaders/glsl%i/blur.fs", GLSL_VERSION));
	mRenderTexture = std::make_unique<RenderTexture2D>(LoadRenderTexture(screenWidth, screenHeight));

	SetCameraMode(*camera, CAMERA_ORBITAL);

	mFxButton = std::make_unique<Sound>(LoadSound("./resources/buttonfx.wav"));
	mButtonTexture = std::make_unique<Texture2D>(LoadTexture("./resources/button.png"));
	frameHeight = (float)mButtonTexture->height / NUM_FRAMES;
	sourceRec = { 0, 0, (float)mButtonTexture->width, frameHeight };
	btnBounds = Rectangle{ ((screenWidth - 120.0f) - (mButtonTexture->width / 2.0f)), (250.0f + (mButtonTexture->height / 3 / 2.0f)), (float)mButtonTexture->width, frameHeight };

	currentShader = (currentShader > FX_GRAYSCALE) ? currentShader = currentShader : currentShader = FX_GRAYSCALE;

	SetWindowSize(screenWidth, screenHeight);
}

void GameScene::Update()
{
	if (applyChanges)
	{
		applyChanges = false;

		if (screenHeight != newScreenHeight || screenWidth != newScreenWidth)
		{
			screenHeight = newScreenHeight;
			screenWidth = newScreenWidth;
			SetWindowSize(screenWidth, screenHeight);
			Exit();
			Enter();
		}
	}

	if (muteAudio)
	{
		SetMasterVolume(0.0f);
		SetSoundVolume(*mFxButton, 0.0f);
		SetMusicVolume(*mMusic, 0.0f);
	}
	else
	{
		SetMasterVolume(masterVolume);
		SetSoundVolume(*mFxButton, sfxVolume);
		SetMusicVolume(*mMusic, musicVolume);
	}

	UpdateMusicStream(*mMusic);

	UpdateCamera(&*camera);              // Update camera

	if (IsKeyPressed(KEY_RIGHT)) currentShader++;
	else if (IsKeyPressed(KEY_LEFT)) currentShader--;

	if (currentShader >= MAX_POSTPRO_SHADERS) currentShader = 0;
	else if (currentShader < 0) currentShader = MAX_POSTPRO_SHADERS - 1;

	mousePoint = GetMousePosition();
	btnAction = false;

	// Check button state
	if (CheckCollisionPointRec(mousePoint, btnBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
		else btnState = 1;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
	}
	else btnState = 0;

	if (btnAction)
	{
		PlaySound(*mFxButton);
		SaveSettings();
	}

	sourceRec.y = btnState * frameHeight;

	timePlayed = GetMusicTimePlayed(*mMusic);

	if (timePlayed >= musicLength)
	{
		SeekMusicStream(*mMusic, 0.0f);
	}
}

void GameScene::Draw()
{
#pragma region 3D_Model
	BeginTextureMode(*mRenderTexture);       // Enable drawing to texture
	ClearBackground(RAYWHITE);  // Clear texture background

	BeginMode3D(*camera);        // Begin 3d mode drawing
	DrawModel(*mModel, modelPosition, 0.1f, WHITE);   // Draw 3d model with texture
	DrawGrid(10, 1.0f);     // Draw a grid
	EndMode3D();                // End 3d mode drawing, returns to orthographic 2d mode
	EndTextureMode();               // End drawing to texture (now we have a texture available for next passes)

	BeginDrawing();
	ClearBackground(RAYWHITE);  // Clear screen background

	// Render generated texture using selected postprocessing shader
	BeginShaderMode(shaders[currentShader]);
	// NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
	DrawTextureRec(mRenderTexture->texture, Rectangle{ 0, 0, (float)mRenderTexture->texture.width, (float)-mRenderTexture->texture.height }, Vector2{ 0, 0 }, WHITE);
	EndShaderMode();

	// Draw 2d shapes and text over drawn texture
	DrawRectangle(0, 9, 580, 30, Fade(LIGHTGRAY, 0.7f));

	DrawText("(c) Church 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);
	DrawText("CURRENT POSTPRO SHADER:", 10, 15, 20, BLACK);
	DrawText(postproShaderText[currentShader], 330, 15, 20, RED);
	DrawText("< >", 540, 10, 30, DARKBLUE);
	DrawFPS(700, 15);
#pragma endregion 3D_Model

	// Draw button
	DrawTextureRec(*mButtonTexture, sourceRec, Vector2{ btnBounds.x, btnBounds.y }, WHITE);

#pragma region Sliders
	// Convert values to strings so slider can detect them
	string screenWidthString = std::to_string(newScreenWidth);
	string screenHeightString = std::to_string(newScreenHeight);
	string masterVolumeString = std::to_string(masterVolume);
	string musicVolumeString = std::to_string(musicVolume);
	string sfxVolumeString = std::to_string(sfxVolume);

	// Window Size Sliders
	newScreenWidth = (int)GuiSliderBar(Rectangle{ (float)screenWidth - 160, 40, 105, 20 }, "Screen Width", screenWidthString.c_str(), (int)newScreenWidth, 800, 1920);
	newScreenHeight = (int)GuiSliderBar(Rectangle{ (float)screenWidth - 160, 70, 105, 20 }, "Screen Height", screenHeightString.c_str(), (int)newScreenHeight, 450, 1080);

	// Audio GUI Options
	masterVolume = (float)GuiSliderBar(Rectangle{ (float)screenWidth - 160, 100, 105, 20 }, "Master Volume", masterVolumeString.c_str(), (float)masterVolume, 0.0f, 1.0f);
	musicVolume = (float)GuiSliderBar(Rectangle{ (float)screenWidth - 160, 130, 105, 20 }, "Music Volume", musicVolumeString.c_str(), (float)musicVolume, 0.0f, 1.0f);
	sfxVolume = (float)GuiSliderBar(Rectangle{ (float)screenWidth - 160, 160, 105, 20 }, "SFX Volume", sfxVolumeString.c_str(), (float)sfxVolume, 0.0f, 1.0f);
	muteAudio = GuiCheckBox(Rectangle{ (float)screenWidth - 160, 190, 20, 20 }, "Mute Audio", muteAudio);
	applyChanges = GuiCheckBox(Rectangle{ (float)screenWidth - 160, 220, 20, 20 }, "Apply Changes?", applyChanges);
#pragma endregion Sliders
}

void GameScene::Exit()
{
	framesCounter = 0;

	for (int i = 0; i < MAX_POSTPRO_SHADERS; i++) UnloadShader(shaders[i]);

	UnloadTexture(*mTexture);         // Unload texture
	UnloadModel(*mModel);             // Unload model
	UnloadRenderTexture(*mRenderTexture);    // Unload render texture
	UnloadTexture(*mButtonTexture);  // Unload button texture

	UnloadSound(*mFxButton);  // Unload sound
	UnloadMusicStream(*mMusic);   // Unload music stream buffers from RAM
	CloseAudioDevice();     // Close audio device
	sqlite3_close(db);
}

void GameScene::LoadSettings()
{
	screenHeight = height;
	screenWidth = width;
	newScreenHeight = height;
	newScreenWidth = width;
	currentShader = shader;
	masterVolume = master;
	sfxVolume = sfx;
	musicVolume = music;
	muteAudio = mute;

	wasDatabaseLoaded = true;
}

void GameScene::SaveSettings()
{
	string displayQuery = "SELECT * FROM Configuration;";
	sqlite3_exec(db, displayQuery.c_str(), Callback, NULL, NULL);

	sqlQuery = std::format("UPDATE Configuration SET Screen_Height = {}, Screen_Width = {}, Master_Volume = {}, SFX_Volume = {}, Music_Volume = {}, Mute_Volume = {}, Shader = {} WHERE User_Profile = 1;", screenHeight, screenWidth, masterVolume, sfxVolume, musicVolume, muteAudio, (int)currentShader);
	int alterTable = sqlite3_exec(db, sqlQuery.c_str(), NULL, 0, &gError);

	if (alterTable == SQLITE_OK)
	{
		std::cout << "\n\nTable modified with success!\n\n";
	}
	else
	{
		std::cout << "\n\nError: " << gError << "\n\n";
	}

	displayQuery = "SELECT * FROM Configuration; ";
	sqlite3_exec(db, displayQuery.c_str(), Callback, NULL, NULL);
}