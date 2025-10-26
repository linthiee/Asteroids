#include "GameLoop.h"
#include "Asteroids.h"
#include "Spaceship.h"
#include "Globals.h"
#include "raylib.h"
#include <string>
#include <time.h>

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID, int& smallAsteroidTextureID);

	static void InitializeWindow();

	static void UpdateDeltaTime();

	static bool IsWindowClosed();

	static void StartDrawing();
	static void FinishDrawing();

	static void BackgroundClear(Color color);

	static void WindowClose();

	static void SetSeed(); 

	static void SetWindow();
}

namespace SCREEN
{
	void Update(int& screenWidth, int& screenHeight);
}

#pragma endregion		

namespace OBJECTS
{
	ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids] = { 0 };
	PLAYER::Spaceship spaceship;
}

namespace ASSETS
{
	Texture tempTexture;
}

void ASTEROIDS::MainLoop()
{
	// initialization 

	ESSENTIALS::SetSeed();

 	ESSENTIALS::Initialization(ASSETS::tempTexture, OBJECTS::spaceship, EXTERNS::bigAsteroidTextureID, EXTERNS::mediumAsteroidTextureID, EXTERNS::smallAsteroidTextureID);
	ESSENTIALS::SetWindow();

	for (int i = 0; i < GLOBALS::maxAsteroids; i++)
	{
		ASTEROIDS::CreateAsteroid(OBJECTS::asteroids[i]);
	}

	PLAYER::CreateSpaceship(OBJECTS::spaceship);


	while (!ESSENTIALS::IsWindowClosed())
	{
		// update
		ESSENTIALS::UpdateDeltaTime();
		SCREEN::Update(EXTERNS::screenWidth, EXTERNS::screenHeight);

		PLAYER::UpdateSpaceship(OBJECTS::spaceship);

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			ASTEROIDS::UpdateAsteroid(OBJECTS::asteroids[i]);
		}

		ESSENTIALS::StartDrawing();
		ESSENTIALS::BackgroundClear(BLACK);

		// draw

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (!OBJECTS::asteroids[i].isActive)
			{
				return;
			}

			ASTEROIDS::DrawAsteroid(OBJECTS::asteroids[i]);
		}

		PLAYER::DrawSpaceship(OBJECTS::spaceship);

		ESSENTIALS::FinishDrawing();
	}
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions


void ESSENTIALS::Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID, int& smallAsteroidTextureID)
{
	ESSENTIALS::InitializeWindow();

	tempTexture = LoadTexture(EXTERNS::spaceshipTexture.c_str());
	spaceship.textureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::bigAsteroidTexture.c_str());
	bigAsteroidTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::mediumAsteroidTexture.c_str());
	mediumAsteroidTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::smallAsteroidTexture.c_str());
	smallAsteroidTextureID = tempTexture.id;
}

void ESSENTIALS::InitializeWindow()
{
	InitWindow(EXTERNS::screenWidth, EXTERNS::screenHeight, ESSENTIALS::title.c_str());
}

void ESSENTIALS::UpdateDeltaTime()
{
	EXTERNS::deltaT = GetFrameTime();
}

bool ESSENTIALS::IsWindowClosed()
{
	return WindowShouldClose();
}

void ESSENTIALS::StartDrawing()
{
	BeginDrawing();
}

void ESSENTIALS::FinishDrawing()
{
	EndDrawing();
}

void ESSENTIALS::BackgroundClear(Color color)
{
	ClearBackground(color);
}

void ESSENTIALS::WindowClose()
{
	CloseWindow();
}

void ESSENTIALS::SetSeed()
{
	SetRandomSeed(static_cast<unsigned int>(time(nullptr)));
}

void ESSENTIALS::SetWindow()
{
	SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void SCREEN::Update(int& screenWidth, int& screenHeight)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();
}
#pragma endregion