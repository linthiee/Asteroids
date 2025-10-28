#include "GameLoop.h"

#include <vector>
#include <iostream>
#include <string>
#include <time.h>

#include "raylib.h"

#include "Asteroids.h"
#include "Spaceship.h"
#include "Bullets.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Utils.h"
#include "Draw.h"
#include "PowerUp.h"

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
		int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
		Sound& asteroidExplosion, Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible, int& bombTextureID,
		int& backgroundTextureID, int& powerupTextureID, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids]);

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
	static bool HasCollided(PLAYER::Spaceship spaceship, BOMB::Bomb bomb);

	static void SpawnMoreAsteroids(ASTEROIDS::Asteroid asteroid[]);

	static void DrawBackground();
}

namespace SCREEN
{
	void Update(int& screenWidth, int& screenHeight);

	void DrawHUD();
}

#pragma endregion		

namespace OBJECTS
{
	struct Cursor
	{
		float radius = 0.5f;
		float positionX = 0.0f;
		float positionY = 0.0f;
	};

	ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids] = { 0 };
	PLAYER::Spaceship spaceship;

	std::vector<BULLETS::Bullets> bullets;
	std::vector<EXPLOSION::Explosion> activeExplosions;

	BOMB::Bomb bomb;
}

namespace STATE
{
	enum class State
	{
		Menu, Play, Credits, Pause, HowToPlay, EndScreen, Exit
	};
}

namespace GAME
{
	STATE::State state = STATE::State::Menu;

	void Update();
	void Draw();
}

namespace ASSETS
{
	Texture tempTexture;
	Texture explosionTexture;
	TEXT::Text score;


	namespace SOUND
	{
		void SetSound(Sound sound);
		void SetPlayingSound();
		//void PauseUnpauseSong(buttons::Button& mute);
		void PauseSounds(Sound sound);
		void UnpauseSound(Sound sound);
	}
}

void ASTEROIDS::MainLoop()
{
	// initialization 
	SetExitKey(KEY_VOLUME_UP);

	ESSENTIALS::Initialization(ASSETS::tempTexture, OBJECTS::spaceship, EXTERNS::bigAsteroidTextureID, EXTERNS::mediumAsteroidTextureID,
		EXTERNS::smallAsteroidTextureID, EXTERNS::firstFrameLaserTextureID, ASSETS::score, EXTERNS::shootEffectSound, EXTERNS::gameHudID,
		EXTERNS::asteroidExplosionSound, EXTERNS::shotgunShotSound, EXTERNS::powerUpShotgunSound, EXTERNS::powerUpSlowSound, EXTERNS::powerUpInvencibleSound,
		EXTERNS::bombTextureID, EXTERNS::backgroundTextureID, EXTERNS::powerUpTextureID, OBJECTS::asteroids);

	STATE::State state = STATE::State::Play;

	while (!ESSENTIALS::IsWindowClosed())
	{
		// update
		switch (state)
		{
		case STATE::State::Menu:
			break;
		case STATE::State::Play:

			GAME::Update();

			break;
		case STATE::State::Credits:
			break;
		case STATE::State::Pause:
			break;
		case STATE::State::HowToPlay:
			break;
		case STATE::State::EndScreen:
			break;
		case STATE::State::Exit:
			break;
		default:
			break;
		}

		// draw

		switch (state)
		{
		case STATE::State::Menu:
			break;
		case STATE::State::Play:

			GAME::Draw();

			break;
		case STATE::State::Credits:
			break;
		case STATE::State::Pause:
			break;
		case STATE::State::HowToPlay:
			break;
		case STATE::State::EndScreen:
			break;
		case STATE::State::Exit:
			break;
		default:
			break;
		}
	}
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions

void ESSENTIALS::Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
	int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
	Sound& asteroidExplosion, Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible, int& bombTextureID,
	int& backgroundTextureID, int& powerupTextureID, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids])
{
	ESSENTIALS::SetSeed();

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

	ASSETS::explosionTexture = LoadTexture(EXTERNS::explosionTexture.c_str());

	tempTexture = LoadTexture(EXTERNS::gameHUD.c_str());
	gameHudID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::firstFrameLaserTexture.c_str());
	firstFrameLaserTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::bombTexture.c_str());
	bombTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::powerUpTexture.c_str());
	powerupTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::backgroundTexture.c_str());
	backgroundTextureID = tempTexture.id;

	shootEffectSound = LoadSound(EXTERNS::shootEffect.c_str());

	asteroidExplosion = LoadSound(EXTERNS::asteroidExplosion.c_str());

	shotgunShot = LoadSound(EXTERNS::shotgunShot.c_str());

	powerUpShotgun = LoadSound(EXTERNS::powerUpShotgun.c_str());

	powerUpSlow = LoadSound(EXTERNS::powerUpSlow.c_str());

	powerUpInvencible = LoadSound(EXTERNS::powerUpInvencible.c_str());

	for (int i = 0; i < EXTERNS::initialMaxAsteroidsOnScreen; i++)
	{
		ASTEROIDS::CreateAsteroid(asteroids[i]);
		EXTERNS::currentAsteroids++;
	}
	PLAYER::CreateSpaceship(spaceship);

	SetWindow();
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

bool ESSENTIALS::HasCollided(PLAYER::Spaceship spaceship, BOMB::Bomb bomb)
{
	float spaceshipPixelX = UTILS::PercentToPixelsX(spaceship.position.x);
	float spaceshipPixelY = UTILS::PercentToPixelsY(spaceship.position.y);
	float bombPixelX = UTILS::PercentToPixelsX(bomb.position.x);
	float bombPixelY = UTILS::PercentToPixelsY(bomb.position.y);

	float distX = spaceshipPixelX - bombPixelX;
	float distY = spaceshipPixelY - bombPixelY;
	float distanceSquared = (distX * distX) + (distY * distY);

	float bombRadius = bomb.radius;
	float spaceshipRadius = spaceship.radius;

	float sumOfRadius = spaceshipRadius + bombRadius;
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
	EXTERNS::currentAsteroids = 0;

	if (EXTERNS::timerSpawn <= 0.0f)
	{
		for (int i = 0; i < GLOBALS::maxAsteroids; i++)
		{
			if (asteroid[i].isActive)
			{
				EXTERNS::currentAsteroids++;
			}
		}

		if (EXTERNS::currentAsteroids < EXTERNS::maxAsteroidsOnScreen)
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

void ESSENTIALS::DrawBackground()
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::backgroundTextureID), 50.0f, 50.0f, 100.0f, 100.0f, WHITE);
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

void GAME::Update()
{

	POWERUP::SetPowerUp(OBJECTS::spaceship.powerUp);

	BOMB::ManageBombSpawn(OBJECTS::bomb);

	ESSENTIALS::UpdateTimers();

	PLAYER::UpdatePowerUp(OBJECTS::spaceship);

	BOMB::UpdateBomb(OBJECTS::bomb);

	SCREEN::Update(EXTERNS::screenWidth, EXTERNS::screenHeight);

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

	if (PLAYER::HasLost(OBJECTS::spaceship))
	{
		PLAYER::SetLife(OBJECTS::spaceship);
		return;
	}

	for (int i = 0; i < OBJECTS::activeExplosions.size(); ++i)
	{
		EXPLOSION::UpdateExplosion(OBJECTS::activeExplosions[i]);
	}

	PLAYER::UpdateSpaceship(OBJECTS::spaceship, ASSETS::score);

	for (int i = 0; i < GLOBALS::maxAsteroids; i++)
	{
		if (!OBJECTS::asteroids[i].isActive)
		{
			continue;
		}

		for (int j = 0; j < OBJECTS::bullets.size(); j++)
		{
			if (OBJECTS::bullets[j].currentLifeSpan > 0.0f && ASTEROIDS::HasCollided(OBJECTS::bullets[j], OBJECTS::asteroids[i]) &&
				OBJECTS::asteroids[i].type == ASTEROIDS::AsteroidType::Small)
			{
				OBJECTS::asteroids[i].isActive = false;
			}

			if (OBJECTS::bullets[j].currentLifeSpan > 0.0f && ASTEROIDS::HasCollided(OBJECTS::bullets[j], OBJECTS::asteroids[i]))
			{
				Vector2 explosionPos = OBJECTS::asteroids[i].position;
				if (OBJECTS::activeExplosions.size() < GLOBALS::maxExplosions)
				{
					EXPLOSION::Explosion newExplosion;

					EXPLOSION::InitExplosion(newExplosion, explosionPos, ASSETS::explosionTexture, 32.0f, 32.0f, 16, 20.0f);

					OBJECTS::activeExplosions.push_back(newExplosion);
				}

				ASTEROIDS::SplitAsteroid(OBJECTS::asteroids[i], OBJECTS::asteroids);

				OBJECTS::asteroids[i].isActive = false;

				EXTERNS::currentAsteroids--;

				OBJECTS::spaceship.score += OBJECTS::asteroids[i].score;

				OBJECTS::bullets[j].currentLifeSpan = 0.0f;

				ASSETS::SOUND::SetSound(EXTERNS::asteroidExplosionSound);

				break;
			}
		}
	}

	for (int i = 0; i < GLOBALS::maxAsteroids; i++)
	{
		if (ESSENTIALS::HasCollided(OBJECTS::spaceship, OBJECTS::asteroids[i]) && OBJECTS::asteroids[i].isActive &&
			!OBJECTS::spaceship.isInvincible && !OBJECTS::spaceship.onSpawnInvincibility)
		{
			PLAYER::UpdateLives(OBJECTS::spaceship);
			PLAYER::ResetSpaceship(OBJECTS::spaceship);
			OBJECTS::asteroids[i].isActive = false;

			ASSETS::SOUND::SetSound(EXTERNS::asteroidExplosionSound);
		}
	}

	if (OBJECTS::bomb.isActive && ESSENTIALS::HasCollided(OBJECTS::spaceship, OBJECTS::bomb) && !OBJECTS::spaceship.isInvincible
		&& !OBJECTS::spaceship.onSpawnInvincibility)
	{
		OBJECTS::bomb.isActive = false;

		PLAYER::UpdateLives(OBJECTS::spaceship);
		PLAYER::ResetSpaceship(OBJECTS::spaceship);

		ASSETS::SOUND::SetSound(EXTERNS::asteroidExplosionSound);
	}

	DeleteBullets(OBJECTS::bullets);
}

void GAME::Draw()
{
	ESSENTIALS::StartDrawing();
	ESSENTIALS::BackgroundClear(BLACK);

	ESSENTIALS::DrawBackground();

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

	if (OBJECTS::bomb.isActive)
	{
		BOMB::DrawBomb(OBJECTS::bomb);
	}

	if (!OBJECTS::spaceship.powerUp.isCollected)
	{
		POWERUP::DrawPowerUp(OBJECTS::spaceship.powerUp);
	}

	for (int i = 0; i < OBJECTS::activeExplosions.size(); ++i)
	{
		if (OBJECTS::activeExplosions[i].isActive)
		{
			EXPLOSION::DrawExplosion(OBJECTS::activeExplosions[i]);
		}
	}

	ESSENTIALS::FinishDrawing();
}

void ASSETS::SOUND::SetSound(Sound sound)
{
	SetSoundVolume(sound, 0.5f);
	PlaySound(sound);
}
//void ASSETS::SOUND::SetPlayingSound()
//{
//	//StopSound(globals::menuSound);
//
//	//PlaySound(globals::playingSound);
//}

//void PauseUnpauseSong(buttons::Button& mute);

//void ASSETS::SOUND::PauseSounds(Sound sound)
//{
//	//if (IsKeyPressed('M') && !mute.isMuted)
//	//{
//	//	mute.isMuted = true;
//	//	PauseSound(globals::playingSound);
//	//}
//	//else if (IsKeyPressed('M') && mute.isMuted)
//	//{
//	//	mute.isMuted = false;
//	//	ResumeSound(globals::playingSound);
//	//}
//}

void ASSETS::SOUND::UnpauseSound(Sound sound)
{
	ResumeSound(sound);
}
#pragma endregion