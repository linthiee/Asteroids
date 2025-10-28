#include "GameLoop.h"
#include "Asteroids.h"
#include "Spaceship.h"
#include "Bullets.h"
#include "Utils.h"
#include "raylib.h"
#include <string>
#include <time.h>
#include <vector>
#include <iostream>

#include "Draw.h"
#include "PowerUp.h"

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
		int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
		Sound& asteroidExplosion, Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible);

	static void InitializeWindow();

	static void UpdateTimers();

	static bool IsWindowClosed();

	static void StartDrawing();
	static void FinishDrawing();

	static void BackgroundClear(Color color);

	static void WindowClose();

	static void SetSeed();

	static void SetWindow();

	static bool HasCollided(PLAYER::Spaceship spaceship, ASTEROIDS::Asteroid asteroid);

	static void SpawnMoreAsteroids(ASTEROIDS::Asteroid asteroid[]);
}

namespace SCREEN
{
	void Update(int& screenWidth, int& screenHeight);

	void DrawHUD();
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
	TEXT::Text score;
}

void ASTEROIDS::MainLoop()
{
	// initialization 

	ESSENTIALS::SetSeed();

	ESSENTIALS::Initialization(ASSETS::tempTexture, OBJECTS::spaceship, EXTERNS::bigAsteroidTextureID, EXTERNS::mediumAsteroidTextureID,
		EXTERNS::smallAsteroidTextureID, EXTERNS::firstFrameLaserTextureID, ASSETS::score, EXTERNS::shootEffectSound, EXTERNS::gameHudID,
		EXTERNS::asteroidExplosionSound, EXTERNS::shotgunShotSound, EXTERNS::powerUpShotgunSound, EXTERNS::powerUpSlowSound, EXTERNS::powerUpInvencibleSound);

	ESSENTIALS::SetWindow();

	for (int i = 0; i < EXTERNS::initialMaxAsteroidsOnScreen; i++)
	{
		ASTEROIDS::CreateAsteroid(OBJECTS::asteroids[i]);
	}

	PLAYER::CreateSpaceship(OBJECTS::spaceship);

	while (!ESSENTIALS::IsWindowClosed())
	{
		// update

		POWERUP::SetPowerUp(OBJECTS::spaceship.powerUp);

		ESSENTIALS::UpdateTimers();

		PLAYER::UpdatePowerUp(OBJECTS::spaceship);

		SCREEN::Update(EXTERNS::screenWidth, EXTERNS::screenHeight);

		PLAYER::UpdateSpaceship(OBJECTS::spaceship, ASSETS::score);

		PLAYER::ApplyPowerUp(OBJECTS::spaceship);

		ESSENTIALS::SpawnMoreAsteroids(OBJECTS::asteroids);

		BULLETS::AssignBulletsOnCreation(OBJECTS::bullets, OBJECTS::spaceship);

		if (OBJECTS::bullets.size() > 0)
		{
			for (int i = 0; i < OBJECTS::bullets.size(); i++)
			{
				BULLETS::UpdateBullet(OBJECTS::bullets[i]);
			}
		}

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (OBJECTS::asteroids[i].isActive)
			{
				ASTEROIDS::UpdateAsteroid(OBJECTS::asteroids[i], OBJECTS::spaceship);
			}
		}

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (!OBJECTS::asteroids[i].isActive)
			{
				continue;
			}

			for (int j = 0; j < OBJECTS::bullets.size(); j++)
			{
				if (OBJECTS::bullets[j].currentLifeSpan > 0.0f && ASTEROIDS::HasCollided(OBJECTS::bullets[j], OBJECTS::asteroids[i]))
				{
					ASTEROIDS::SplitAsteroid(OBJECTS::asteroids[i], OBJECTS::asteroids);

					OBJECTS::asteroids[i].isActive = false;

					OBJECTS::spaceship.score += OBJECTS::asteroids[i].score;

					OBJECTS::bullets[j].currentLifeSpan = 0.0f;

					PlaySound(EXTERNS::asteroidExplosionSound);

					break;
				}
			}
		}

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (ESSENTIALS::HasCollided(OBJECTS::spaceship, OBJECTS::asteroids[i]) && OBJECTS::asteroids[i].isActive && !OBJECTS::spaceship.isInvincible)
			{
				PLAYER::UpdateLives(OBJECTS::spaceship);
				PLAYER::ResetSpaceship(OBJECTS::spaceship);
				OBJECTS::asteroids[i].isActive = false;

				PlaySound(EXTERNS::asteroidExplosionSound);
			}
		}

		DeleteBullets(OBJECTS::bullets);

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
			if (OBJECTS::asteroids[i].isActive)
			{
				ASTEROIDS::DrawAsteroid(OBJECTS::asteroids[i]);
			}
		}

		SCREEN::DrawHUD();

		if (!OBJECTS::spaceship.powerUp.isCollected)
		{
			POWERUP::DrawPowerUp(OBJECTS::spaceship.powerUp);
		}

		ESSENTIALS::FinishDrawing();
	}
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions

void ESSENTIALS::Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
	int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
	Sound& asteroidExplosion,  Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible)
{
	ESSENTIALS::InitializeWindow();
	InitAudioDevice();

	score.text = "Score: " + std::to_string(spaceship.score);

	EXTERNS::defaultText.font = LoadFont(EXTERNS::fontText.c_str());

	score.font = EXTERNS::defaultText.font;

	score.posX = 90;
	score.posY = 3;

	tempTexture = LoadTexture(EXTERNS::spaceshipTexture.c_str());
	spaceship.textureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::bigAsteroidTexture.c_str());
	bigAsteroidTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::mediumAsteroidTexture.c_str());
	mediumAsteroidTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::smallAsteroidTexture.c_str());
	smallAsteroidTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::gameHUD.c_str());
	gameHudID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::firstFrameLaserTexture.c_str());
	firstFrameLaserTextureID = tempTexture.id;

	shootEffectSound = LoadSound(EXTERNS::shootEffect.c_str());

	asteroidExplosion = LoadSound(EXTERNS::asteroidExplosion.c_str());

	shotgunShot = LoadSound(EXTERNS::shotgunShot.c_str());

	powerUpShotgun = LoadSound(EXTERNS::powerUpShotgun.c_str());

	powerUpSlow = LoadSound(EXTERNS::powerUpSlow.c_str());

	powerUpInvencible = LoadSound(EXTERNS::powerUpInvencible.c_str());
}

void ESSENTIALS::InitializeWindow()
{
	InitWindow(EXTERNS::screenWidth, EXTERNS::screenHeight, ESSENTIALS::title.c_str());
}

void ESSENTIALS::UpdateTimers()
{
	EXTERNS::deltaT = GetFrameTime();
	//time per frame
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

bool ESSENTIALS::HasCollided(PLAYER::Spaceship spaceship, ASTEROIDS::Asteroid asteroid)
{
	float spaceshipPixelX = UTILS::PercentToPixelsX(spaceship.position.x);
	float spaceshipPixelY = UTILS::PercentToPixelsY(spaceship.position.y);
	float asteroidPixelX = UTILS::PercentToPixelsX(asteroid.position.x);
	float asteroidPixelY = UTILS::PercentToPixelsY(asteroid.position.y);

	float distX = spaceshipPixelX - asteroidPixelX;
	float distY = spaceshipPixelY - asteroidPixelY;
	float distanceSquared = (distX * distX) + (distY * distY);

	float asteroidRadius = static_cast<float>(asteroid.radius * static_cast<int>(asteroid.size));
	float spaceshipRadius = spaceship.radius;

	float sumOfRadius = asteroidRadius + spaceshipRadius;
	float sumOfRadiusSquared = sumOfRadius * sumOfRadius;

	return distanceSquared <= sumOfRadiusSquared;
}

void ESSENTIALS::SpawnMoreAsteroids(ASTEROIDS::Asteroid asteroid[])
{
	EXTERNS::difficultyTimer -= EXTERNS::deltaT;

	if (EXTERNS::difficultyTimer <= 0.0f)
	{
		if (EXTERNS::initialMaxAsteroidsOnScreen < EXTERNS::maxAsteroidsOnScreen)
		{
			EXTERNS::maxAsteroidsOnScreen++;
		}
		EXTERNS::difficultyTimer = EXTERNS::timerToIncreaseDifficulty;
	}

	EXTERNS::timerSpawn -= EXTERNS::deltaT;

	if (EXTERNS::timerSpawn <= 0.0f)
	{
		int currentAsteroids = 0;

		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (asteroid[i].isActive)
			{
				currentAsteroids++;
			}
		}

		if (currentAsteroids < EXTERNS::maxAsteroidsOnScreen)
		{
			for (int i = 0; i < GLOBALS::maxAsteroids; i++)
			{
				if (!asteroid[i].isActive)
				{
					ASTEROIDS::Asteroid& newAsteroid = asteroid[i];
					ASTEROIDS::CreateAsteroid(newAsteroid);

					break;
				}
			}
		}
		EXTERNS::timerSpawn = EXTERNS::spawnTime;
	}
}

void SCREEN::Update(int& screenWidth, int& screenHeight)
{
	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();
}

void SCREEN::DrawHUD()
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::gameHudID), 50.0f, 50.0f, 100.0f, 100.0f, WHITE);
	PLAYER::DrawLives(OBJECTS::spaceship);
	DRAW::DrawText(ASSETS::score);
}
#pragma endregion