#include "GameLoop.h"
#include "Asteroids.h"
#include "Spaceship.h"
#include "Bullets.h"
#include "Globals.h"
#include "raylib.h"
#include <string>
#include <time.h>
#include <vector>

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID, int& smallAsteroidTextureID, int& firstFrameLaserTextureID);

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

	std::vector<BULLETS::Bullets> bullets;
}

namespace ASSETS
{
	Texture tempTexture;
}

void ASTEROIDS::MainLoop()
{
	// initialization 

	ESSENTIALS::SetSeed();

	ESSENTIALS::Initialization(ASSETS::tempTexture, OBJECTS::spaceship, EXTERNS::bigAsteroidTextureID, EXTERNS::mediumAsteroidTextureID, EXTERNS::smallAsteroidTextureID, EXTERNS::firstFrameLaserTextureID);
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

		BULLETS::AssignBulletsOnCreation(OBJECTS::bullets, OBJECTS::spaceship);
		
		if (OBJECTS::bullets.size() > 0)
		{
			for (int i = 0; i < OBJECTS::bullets.size(); i++)
			{
				BULLETS::UpdateBullet(OBJECTS::bullets[i]);
			}
		}

		DeleteBullets(OBJECTS::bullets);

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			ASTEROIDS::UpdateAsteroid(OBJECTS::asteroids[i]);
		}

		ESSENTIALS::StartDrawing();
		ESSENTIALS::BackgroundClear(BLACK);

		// draw

		PLAYER::DrawSpaceship(OBJECTS::spaceship);

		if (OBJECTS::bullets.size() > 0)
		{
			for (int i = 0; i < OBJECTS::bullets.size(); i++)
			{
				BULLETS::DrawBullet(OBJECTS::bullets[i]);
			}
		}

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (!OBJECTS::asteroids[i].isActive)
			{
				return;
			}

			ASTEROIDS::DrawAsteroid(OBJECTS::asteroids[i]);
		}

		ESSENTIALS::FinishDrawing();
	}
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions


void ESSENTIALS::Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID, int& smallAsteroidTextureID, int& firstFrameLaserTextureID)
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

	tempTexture = LoadTexture(EXTERNS::firstFrameLaserTexture.c_str());
	firstFrameLaserTextureID = tempTexture.id;
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