#include "GameLoop.h"
#include "Asteroids.h"
#include "Globals.h"
#include <string>
#include <ctime>

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void InitializeWindow();

	static void UpdateDeltaTime();

	static bool IsWindowClosed();

	static void StartDrawing();
	static void FinishDrawing();

	static void BackgroundClear(Color color);

	static void WindowClose();

	static void SetSeed(); 
}
#pragma endregion		

namespace OBJECTS
{
	ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids] = { 0 };
}

void ASTEROIDS::MainLoop()
{
	// initialization 

	ESSENTIALS::SetSeed();

	for (int i = 0; i < GLOBALS::maxAsteroids; i++)
	{
		ASTEROIDS::CreateAsteroid(OBJECTS::asteroids[i]);
	}

	ESSENTIALS::InitializeWindow();

	while (!ESSENTIALS::IsWindowClosed())
	{
		// update
		ESSENTIALS::UpdateDeltaTime();

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

		ESSENTIALS::FinishDrawing();
	}
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions


void ESSENTIALS::InitializeWindow()
{
	InitWindow(GLOBALS::screenWidth, GLOBALS::screenHeight, ESSENTIALS::title.c_str());
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

#pragma endregion