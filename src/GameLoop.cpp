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
#include "Button.h"

#pragma region	Game_Essentials_Declarations

namespace ESSENTIALS
{
	static const std::string title = "Asteroids";

	static void Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
		int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
		Sound& asteroidExplosion, Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible, int& bombTextureID,
		int& backgroundTextureID, int& powerupTextureID, Sound& bombExplosion, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids],
		Sound& menuSound, Sound& playSound, int& menuTextureID, int& buttonTextureID, int& titleTextureID,
		BUTTONS::Button& play, BUTTONS::Button& settings, BUTTONS::Button& credits, BUTTONS::Button& howToPlay, BUTTONS::Button& exit,
		BUTTONS::Button& pause, BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& fullscreenButton,
		BUTTONS::Button& returnFromCredits);

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

	static void UpdateMousePosition(Cursor& cursor);

	Cursor cursor;

	ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids] = { 0 };
	PLAYER::Spaceship spaceship;

	std::vector<BULLETS::Bullets> bullets;
	std::vector<EXPLOSION::Explosion> activeExplosions;

	BOMB::Bomb bomb;
}

namespace GAME
{
	namespace STATE
	{
		enum class State
		{
			Menu, Play, Credits, Pause, HowToPlay, EndScreen, Settings, Exit
		};
	}
	STATE::State state = STATE::State::Menu;

	void Initialize(PLAYER::Spaceship& spaceship, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids]);
	void Update();
	void Draw();

	namespace MENU
	{
		void Update(BUTTONS::Button& play, BUTTONS::Button& settings, BUTTONS::Button& credits, BUTTONS::Button& howToPlay, BUTTONS::Button& exit, OBJECTS::Cursor& cursor, STATE::State& currentState);
		void Draw(BUTTONS::Button playText, BUTTONS::Button settings, BUTTONS::Button creditsText, BUTTONS::Button howToPlayText, BUTTONS::Button exitText);
	}

	namespace PAUSE
	{
		void Update(OBJECTS::Cursor& cursor, STATE::State& currentState, BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& exit);
		void Draw(BUTTONS::Button pause, BUTTONS::Button returnButt, BUTTONS::Button retry, BUTTONS::Button exit);
	}

	namespace SETTINGS
	{
		void Update(OBJECTS::Cursor& cursor, STATE::State& currentState, BUTTONS::Button& fullscreenToggle, BUTTONS::Button& returnButton);
		void Draw(BUTTONS::Button& fullscreenToggle, BUTTONS::Button& returnButton);
	}

	namespace CREDITS
	{
		void Update(STATE::State& currentState, OBJECTS::Cursor& cursor, BUTTONS::Button& returnButton);
		void Draw(BUTTONS::Button& returnButton);
	}

	namespace HOWTOPLAY
	{
		void Update(STATE::State& currentState, OBJECTS::Cursor& cursor, BUTTONS::Button& returnButton);
		void Draw(BUTTONS::Button& returnButton);
	}

	namespace ENDSCREEN
	{
		void Update(OBJECTS::Cursor& cursor, STATE::State& currentState, BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& exit);
		void Draw(BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& exit);
	}
	void Deinitialize(Texture& tempTexture);
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
		void PauseSong(Sound sound);
		void UnpauseSound(Sound sound);
	}
}

namespace BUTTONS
{
	Button settings;
	Button play;
	Button credits;
	Button howToPlay;
	Button exit;

	Button pause;
	Button returnButt;
	Button retry;

	Button fullscreenToggle;
	Button returnFromCredits;
}

void ASTEROIDS::MainLoop()
{
	// initialization 

	ESSENTIALS::Initialization(ASSETS::tempTexture, OBJECTS::spaceship, EXTERNS::bigAsteroidTextureID, EXTERNS::mediumAsteroidTextureID,
		EXTERNS::smallAsteroidTextureID, EXTERNS::firstFrameLaserTextureID, ASSETS::score, EXTERNS::shootEffectSound, EXTERNS::gameHudID,
		EXTERNS::asteroidExplosionSound, EXTERNS::shotgunShotSound, EXTERNS::powerUpShotgunSound, EXTERNS::powerUpSlowSound, EXTERNS::powerUpInvencibleSound,
		EXTERNS::bombTextureID, EXTERNS::backgroundTextureID, EXTERNS::powerUpTextureID, EXTERNS::bombExplosionSound, OBJECTS::asteroids,
		EXTERNS::menuSound, EXTERNS::playSound, EXTERNS::menuTextureID, EXTERNS::buttonTextureID, EXTERNS::titleTextureID,
		BUTTONS::play, BUTTONS::settings, BUTTONS::credits, BUTTONS::howToPlay, BUTTONS::exit, BUTTONS::pause, BUTTONS::returnButt, BUTTONS::retry,
		BUTTONS::fullscreenToggle, BUTTONS::returnFromCredits);

	SetExitKey(KEY_VOLUME_UP);

	SetSoundVolume(EXTERNS::menuSound, 0.3f);
	PlaySound(EXTERNS::menuSound);

	while (!ESSENTIALS::IsWindowClosed() && GAME::state != GAME::STATE::State::Exit)
	{
		// update
		switch (GAME::state)
		{
		case GAME::STATE::State::Menu:

			GAME::MENU::Update(BUTTONS::play, BUTTONS::settings, BUTTONS::credits, BUTTONS::howToPlay, BUTTONS::exit, OBJECTS::cursor, GAME::state);
			SCREEN::Update(EXTERNS::screenWidth, EXTERNS::screenHeight);

			ASSETS::SOUND::PauseSong(EXTERNS::playSound);

			if (!IsSoundPlaying(EXTERNS::menuSound))
			{
				SetSoundVolume(EXTERNS::menuSound, 0.3f);
				PlaySound(EXTERNS::menuSound);
			}

			if (EXTERNS::retry)
			{
				for (int i = 0; i < GLOBALS::maxAsteroids; i++)
				{
					OBJECTS::asteroids[i] = ASTEROIDS::Asteroid();
				}

				OBJECTS::activeExplosions.clear();
				OBJECTS::bullets.clear();

				GAME::Initialize(OBJECTS::spaceship, OBJECTS::asteroids);
				GAME::state = GAME::STATE::State::Play;
				EXTERNS::retry = false;
			}
			if (GAME::state == GAME::STATE::State::Play)
			{
				for (int i = 0; i < GLOBALS::maxAsteroids; i++)
				{
					OBJECTS::asteroids[i] = ASTEROIDS::Asteroid();
				}

				OBJECTS::activeExplosions.clear();
				OBJECTS::bullets.clear();

				GAME::Initialize(OBJECTS::spaceship, OBJECTS::asteroids);
				ASSETS::SOUND::PauseSong(EXTERNS::playSound);
				ASSETS::SOUND::SetPlayingSound();
			}

			break;
		case GAME::STATE::State::Play:

			GAME::Update();

			break;
		case GAME::STATE::State::Credits:

			GAME::CREDITS::Update(GAME::state, OBJECTS::cursor, BUTTONS::returnFromCredits);

			break;
		case GAME::STATE::State::Pause:

			GAME::PAUSE::Update(OBJECTS::cursor, GAME::state, BUTTONS::returnButt, BUTTONS::retry, BUTTONS::exit);

			if (GAME::state == GAME::STATE::State::Menu)
			{
				ASSETS::SOUND::PauseSong(EXTERNS::playSound);
				ASSETS::SOUND::SetSound(EXTERNS::menuSound);
			}

			break;
		case GAME::STATE::State::HowToPlay:

			GAME::HOWTOPLAY::Update(GAME::state, OBJECTS::cursor, BUTTONS::returnFromCredits);

			break;
		case GAME::STATE::State::EndScreen:

			GAME::ENDSCREEN::Update(OBJECTS::cursor, GAME::state, BUTTONS::returnButt, BUTTONS::retry, BUTTONS::exit);

			break;
		case GAME::STATE::State::Settings:

			GAME::SETTINGS::Update(OBJECTS::cursor, GAME::state, BUTTONS::fullscreenToggle, BUTTONS::returnButt);

			break;
		case GAME::STATE::State::Exit:
			break;
		default:
			break;
		}

		SCREEN::Update(EXTERNS::screenWidth, EXTERNS::screenHeight);

		// draw
		ESSENTIALS::StartDrawing();
		ESSENTIALS::BackgroundClear(BLACK);

		switch (GAME::state)
		{
		case GAME::STATE::State::Menu:

			if (!EXTERNS::retry)
			{
				GAME::MENU::Draw(BUTTONS::play, BUTTONS::settings, BUTTONS::credits, BUTTONS::howToPlay, BUTTONS::exit);
			}
			else
			{
				GAME::Draw();
			}

			break;
		case GAME::STATE::State::Play:

			GAME::Draw();

			break;
		case GAME::STATE::State::Credits:

			GAME::CREDITS::Draw(BUTTONS::returnFromCredits);

			break;
		case GAME::STATE::State::Pause:

			GAME::Draw();
			GAME::PAUSE::Draw(BUTTONS::pause, BUTTONS::returnButt, BUTTONS::retry, BUTTONS::exit);

			break;
		case GAME::STATE::State::HowToPlay:

			GAME::HOWTOPLAY::Draw(BUTTONS::returnFromCredits);

			break;
		case GAME::STATE::State::EndScreen:

			GAME::Draw();
			GAME::ENDSCREEN::Draw(BUTTONS::returnButt, BUTTONS::retry, BUTTONS::exit);

			break;
		case GAME::STATE::State::Settings:

			GAME::SETTINGS::Draw(BUTTONS::fullscreenToggle, BUTTONS::returnButt);

			break;
		case GAME::STATE::State::Exit:
			break;
		default:
			break;
		}
		ESSENTIALS::FinishDrawing();
	}
	GAME::Deinitialize(ASSETS::tempTexture);
	ESSENTIALS::WindowClose();
}

#pragma region Game_Essential_Definitions

void ESSENTIALS::Initialization(Texture& tempTexture, PLAYER::Spaceship& spaceship, int& bigAsteroidTextureID, int& mediumAsteroidTextureID,
	int& smallAsteroidTextureID, int& firstFrameLaserTextureID, TEXT::Text& score, Sound& shootEffectSound, int& gameHudID,
	Sound& asteroidExplosion, Sound& shotgunShot, Sound& powerUpShotgun, Sound& powerUpSlow, Sound& powerUpInvencible, int& bombTextureID,
	int& backgroundTextureID, int& powerupTextureID, Sound& bombExplosion, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids],
	Sound& menuSound, Sound& playSound, int& menuTextureID, int& buttonTextureID, int& titleTextureID, BUTTONS::Button& play,
	BUTTONS::Button& settings, BUTTONS::Button& credits, BUTTONS::Button& howToPlay, BUTTONS::Button& exit,
	BUTTONS::Button& pause, BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& fullscreenButton, BUTTONS::Button& returnFromCredits)
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

	tempTexture = LoadTexture(EXTERNS::menuTexture.c_str());
	menuTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::buttonTexture.c_str());
	buttonTextureID = tempTexture.id;

	tempTexture = LoadTexture(EXTERNS::titleTexture.c_str());
	titleTextureID = tempTexture.id;

	shootEffectSound = LoadSound(EXTERNS::shootEffect.c_str());

	asteroidExplosion = LoadSound(EXTERNS::asteroidExplosion.c_str());

	shotgunShot = LoadSound(EXTERNS::shotgunShot.c_str());

	powerUpShotgun = LoadSound(EXTERNS::powerUpShotgun.c_str());

	powerUpSlow = LoadSound(EXTERNS::powerUpSlow.c_str());

	powerUpInvencible = LoadSound(EXTERNS::powerUpInvencible.c_str());

	bombExplosion = LoadSound(EXTERNS::bombExplosion.c_str());

	menuSound = LoadSound(EXTERNS::menuSong.c_str());

	playSound = LoadSound(EXTERNS::playSong.c_str());

	float buttonWidth = 25.0f;
	float buttonHeight = 8.0f;
	float buttonCenterX = 50.0f;

	play.text.font = EXTERNS::defaultText.font;
	play.text.text = "PLAY";
	BUTTONS::Initialize(play, buttonWidth, buttonHeight, buttonCenterX, 35.0f);

	credits.text.font = EXTERNS::defaultText.font;
	credits.text.text = "CREDITS";
	BUTTONS::Initialize(credits, buttonWidth, buttonHeight, buttonCenterX, 45.0f);

	settings.text.font = EXTERNS::defaultText.font;
	settings.text.text = "SETTINGS";
	BUTTONS::Initialize(settings, buttonWidth, buttonHeight, buttonCenterX, 55.0f);

	howToPlay.text.font = EXTERNS::defaultText.font;
	howToPlay.text.text = "HOW TO PLAY";
	BUTTONS::Initialize(howToPlay, buttonWidth * 1.6f, buttonHeight, buttonCenterX, 65.0f);

	exit.text.font = EXTERNS::defaultText.font;
	exit.text.text = "EXIT";
	BUTTONS::Initialize(exit, buttonWidth, buttonHeight, buttonCenterX, 75.0f);

	pause.text.font = EXTERNS::defaultText.font;
	pause.text.text = "GAME PAUSED";
	BUTTONS::Initialize(pause, buttonWidth * 1.6f, buttonHeight, buttonCenterX, 25.0f);

	retry.text.font = EXTERNS::defaultText.font;
	retry.text.text = "RETRY";
	BUTTONS::Initialize(retry, buttonWidth, buttonHeight, buttonCenterX - 10.0f, 55.0f);

	returnButt.text.font = EXTERNS::defaultText.font;
	returnButt.text.text = "MENU";
	BUTTONS::Initialize(returnButt, buttonWidth, buttonHeight, buttonCenterX + 10.0f, 55.0f);

	fullscreenButton.text.font = EXTERNS::defaultText.font;
	fullscreenButton.text.text = "TOGGLE FULLSCREEN";
	BUTTONS::Initialize(fullscreenButton, buttonWidth * 2.0f, buttonHeight, buttonCenterX, 25.0f);

	returnFromCredits.text.font = EXTERNS::defaultText.font;
	returnFromCredits.text.text = "MENU";
	BUTTONS::Initialize(returnFromCredits, buttonWidth * 2.0f, buttonHeight, buttonCenterX, 85.0f);

	GAME::Initialize(spaceship, asteroids);

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

void OBJECTS::UpdateMousePosition(OBJECTS::Cursor& cursorParam)
{
	cursorParam.positionX = UTILS::PixelsToPercentX(GetMousePosition().x);
	cursorParam.positionY = UTILS::PixelsToPercentY(GetMousePosition().y);
}

void GAME::Initialize(PLAYER::Spaceship& spaceship, ASTEROIDS::Asteroid asteroids[GLOBALS::maxAsteroids])
{
	EXTERNS::currentAsteroids = 0;

	for (int i = 0; i < EXTERNS::initialMaxAsteroidsOnScreen; i++)
	{
		ASTEROIDS::CreateAsteroid(asteroids[i]);
		EXTERNS::currentAsteroids++;
	}

	PLAYER::CreateSpaceship(spaceship);
}

void GAME::Update()
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		EXTERNS::gamePaused = true;
		GAME::state = GAME::STATE::State::Pause;
	}

	if (!IsSoundPlaying(EXTERNS::playSound))
	{
		ASSETS::SOUND::SetPlayingSound();
	}

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
		GAME::state = GAME::STATE::State::EndScreen;
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

		ASSETS::SOUND::SetSound(EXTERNS::bombExplosionSound);
	}

	DeleteBullets(OBJECTS::bullets);
}

void GAME::Draw()
{
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
}

void ASSETS::SOUND::SetSound(Sound sound)
{
	SetSoundVolume(sound, 0.5f);
	PlaySound(sound);
}
void ASSETS::SOUND::SetPlayingSound()
{
	StopSound(EXTERNS::menuSound);

	SetSoundVolume(EXTERNS::playSound, 0.2f);
	PlaySound(EXTERNS::playSound);
}

void ASSETS::SOUND::PauseSong(Sound sound)
{
	PauseSound(sound);
}

void ASSETS::SOUND::UnpauseSound(Sound sound)
{
	ResumeSound(sound);
}

void GAME::MENU::Update(BUTTONS::Button& play, BUTTONS::Button& settings, BUTTONS::Button& credits, BUTTONS::Button& howToPlay, BUTTONS::Button& exit, OBJECTS::Cursor& cursor, STATE::State& currentState)
{
	OBJECTS::UpdateMousePosition(cursor);

	Rectangle playButt = { play.position.x - play.width / 2, play.position.y - play.height / 2, play.width, play.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, playButt))
	{
		play.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Play;
		}
	}
	else
	{
		play.text.color = GRAY;
	}

	Rectangle creditsButt = { credits.position.x - credits.width / 2, credits.position.y - credits.height / 2, credits.width, credits.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, creditsButt))
	{
		credits.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Credits;
		}
	}
	else
	{
		credits.text.color = GRAY;
	}

	Rectangle settingsButt = { settings.position.x - settings.width / 2, settings.position.y - settings.height / 2, settings.width, settings.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, settingsButt))
	{
		settings.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Settings;
		}
	}
	else
	{
		settings.text.color = GRAY;
	}

	Rectangle howToPlayButt = { howToPlay.position.x - howToPlay.width / 2, howToPlay.position.y - howToPlay.height / 2, howToPlay.width, howToPlay.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, howToPlayButt))
	{
		howToPlay.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::HowToPlay;
		}
	}
	else
	{
		howToPlay.text.color = GRAY;
	}

	Rectangle exitButt = { exit.position.x - exit.width / 2, exit.position.y - exit.height / 2, exit.width, exit.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, exitButt))
	{
		exit.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Exit;
		}
	}
	else
	{
		exit.text.color = GRAY;
	}
}

void GAME::MENU::Draw(BUTTONS::Button play, BUTTONS::Button settings, BUTTONS::Button credits, BUTTONS::Button howToPlay, BUTTONS::Button exit)
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::backgroundTextureID), 50, 50, 100, 100, WHITE);
	DRAW::DrawSprite(static_cast<float>(EXTERNS::titleTextureID), 54.0f, 15.0f, 40.0f, 30.0f, WHITE);

	BUTTONS::Draw(play);
	BUTTONS::Draw(credits);
	BUTTONS::Draw(settings);
	BUTTONS::Draw(howToPlay);
	BUTTONS::Draw(exit);
}

void GAME::PAUSE::Update(OBJECTS::Cursor& cursor, GAME::STATE::State& currentState, BUTTONS::Button& returnButt, BUTTONS::Button& retry,
	BUTTONS::Button& exit)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		currentState = GAME::STATE::State::Play;
		EXTERNS::gamePaused = false;
		return;
	}

	OBJECTS::UpdateMousePosition(cursor);

	Rectangle returnButton = { returnButt.position.x - returnButt.width / 2, returnButt.position.y - returnButt.height / 2, returnButt.width, returnButt.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, returnButton))
	{
		returnButt.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		returnButt.text.color = GRAY;
	}

	Rectangle retryButt = { retry.position.x - retry.width / 2, retry.position.y - retry.height / 2, retry.width, retry.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, retryButt))
	{
		retry.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			EXTERNS::retry = true;
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		retry.text.color = GRAY;
	}

	Rectangle exitButt = { exit.position.x - exit.width / 2, exit.position.y - exit.height / 2, exit.width, exit.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, exitButt))
	{
		exit.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Exit;
		}
	}
	else
	{
		exit.text.color = GRAY;
	}
}

void GAME::PAUSE::Draw(BUTTONS::Button pause, BUTTONS::Button returnButt, BUTTONS::Button retry, BUTTONS::Button exit)
{
	BUTTONS::Draw(pause);
	BUTTONS::Draw(returnButt);
	BUTTONS::Draw(retry);
	BUTTONS::Draw(exit);
}

void GAME::SETTINGS::Update(OBJECTS::Cursor& cursor, STATE::State& currentState, BUTTONS::Button& fullscreenToggle, BUTTONS::Button& returnButton)
{
	OBJECTS::UpdateMousePosition(cursor);

	Rectangle fullscreenButt = { fullscreenToggle.position.x - fullscreenToggle.width / 2, fullscreenToggle.position.y - fullscreenToggle.height / 2, fullscreenToggle.width, fullscreenToggle.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, fullscreenButt))
	{
		fullscreenToggle.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			ToggleFullscreen();
		}
	}
	else
	{
		fullscreenToggle.text.color = GRAY;
	}

	Rectangle returnButtonRect = { returnButton.position.x - returnButton.width / 2, returnButton.position.y - returnButton.height / 2, returnButton.width, returnButton.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, returnButtonRect))
	{
		returnButton.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		returnButton.text.color = GRAY;
	}
}

void GAME::SETTINGS::Draw(BUTTONS::Button& fullscreenToggle, BUTTONS::Button& returnButton)
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::menuTextureID), 50, 50, 100, 100, WHITE);

	BUTTONS::Draw(fullscreenToggle);
	BUTTONS::Draw(returnButton);
}

void GAME::CREDITS::Update(STATE::State& currentState, OBJECTS::Cursor& cursor, BUTTONS::Button& returnFromCredits)
{
	OBJECTS::UpdateMousePosition(cursor);

	returnFromCredits.color = WHITE;

	Rectangle returnButtonRect = { returnFromCredits.position.x - returnFromCredits.width / 2, returnFromCredits.position.y - returnFromCredits.height / 2, returnFromCredits.width, returnFromCredits.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, returnButtonRect))
	{
		returnFromCredits.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		returnFromCredits.text.color = GRAY;
	}
}

void GAME::CREDITS::Draw(BUTTONS::Button& returnButton)
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::menuTextureID), 50, 50, 100, 100, WHITE);

	TEXT::Text credits1;
	credits1.font = EXTERNS::defaultText.font;
	credits1.fonstSize = 30;
	credits1.posX = 20.0f;
	credits1.posY = 20.0f;
	credits1.text = "Programming made by:\n Eluney Jazmin Mousseigne";

	TEXT::Text credits2;
	credits2.font = EXTERNS::defaultText.font;
	credits2.fonstSize = 30;
	credits2.posX = 30.0f;
	credits2.posY = 30.0f;
	credits2.text = "Art made by:\n Laura Srur & Eluney Jazmin Mousseigne ";

	TEXT::Text credits3;
	credits3.font = EXTERNS::defaultText.font;
	credits3.fonstSize = 30;
	credits3.posX = 30.0f;
	credits3.posY = 40.0f;
	credits3.text = "Sounds from:\n Menu & Gameplay: \nRetro 8-bit RPG Music Pack by May Genko";

	TEXT::Text credits4;
	credits4.font = EXTERNS::defaultText.font;
	credits4.fonstSize = 20;
	credits4.posX = 32.0f;
	credits4.posY = 52.0f;
	credits4.text = "(https://maygenko.itch.io/retro-8-bit-rpg-music-pack-by-may-genko)";

	TEXT::Text credits5;
	credits5.font = EXTERNS::defaultText.font;
	credits5.fonstSize = 30;
	credits5.posX = 30.0f;
	credits5.posY = 60.0f;
	credits5.text = "Sound Effects: Pixel combat by Helton Yan\n(https://heltonyan.itch.io/pixelcombat)";

	DRAW::DrawText(credits1);
	DRAW::DrawText(credits2);
	DRAW::DrawText(credits3);
	DRAW::DrawText(credits4);
	DRAW::DrawText(credits5);

	BUTTONS::Draw(returnButton);
}

void GAME::HOWTOPLAY::Update(STATE::State& currentState, OBJECTS::Cursor& cursor, BUTTONS::Button& returnButton)
{
	OBJECTS::UpdateMousePosition(cursor);

	returnButton.color = WHITE;

	Rectangle returnButtonRect = { returnButton.position.x - returnButton.width / 2, returnButton.position.y - returnButton.height / 2, returnButton.width, returnButton.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, returnButtonRect))
	{
		returnButton.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		returnButton.text.color = GRAY;
	}
}

void GAME::HOWTOPLAY::Draw(BUTTONS::Button& returnButton)
{
	DRAW::DrawSprite(static_cast<float>(EXTERNS::menuTextureID), 50, 50, 100, 100, WHITE);

	TEXT::Text howToPlay1;
	howToPlay1.font = EXTERNS::defaultText.font;
	howToPlay1.fonstSize = 20;
	howToPlay1.posX = 45.0f;
	howToPlay1.posY = 20.0f;
	howToPlay1.text = "Use left mouse button click to shoot and right mouse button click to accelerate!";

	TEXT::Text howToPlay2;
	howToPlay2.font = EXTERNS::defaultText.font;
	howToPlay2.fonstSize = 20;
	howToPlay2.posX = 46.0f;
	howToPlay2.posY = 30.0f;
	howToPlay2.text = "There are different powerups that can randomly appear\n they could upgrade your wepon, slow the asteroids and even make you invincible!";

	TEXT::Text howToPlay3;
	howToPlay3.font = EXTERNS::defaultText.font;
	howToPlay3.fonstSize = 20;
	howToPlay3.posX = 40.0f;
	howToPlay3.posY = 40.0f;
	howToPlay3.text = "From time to time a bomb will come passing by. Dont let it hit you.";

	TEXT::Text howToPlay4;
	howToPlay4.font = EXTERNS::defaultText.font;
	howToPlay4.fonstSize = 20;
	howToPlay4.posX = 45.0f;
	howToPlay4.posY = 60.0f;
	howToPlay4.text = "If you lose all three lives you will lose! On spawn you will be invincible for a few seconds";

	DRAW::DrawText(howToPlay1);
	DRAW::DrawText(howToPlay2);
	DRAW::DrawText(howToPlay3);
	DRAW::DrawText(howToPlay4);

	BUTTONS::Draw(returnButton);
}

void GAME::ENDSCREEN::Update(OBJECTS::Cursor& cursor, STATE::State& currentState, BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& exit)
{
	OBJECTS::UpdateMousePosition(cursor);

	Rectangle returnButton = { returnButt.position.x - returnButt.width / 2, returnButt.position.y - returnButt.height / 2, returnButt.width, returnButt.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, returnButton))
	{
		returnButt.text.color = WHITE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		returnButt.text.color = GRAY;
	}

	Rectangle retryButt = { retry.position.x - retry.width / 2, retry.position.y - retry.height / 2, retry.width, retry.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, retryButt))
	{
		retry.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			EXTERNS::retry = true;
			currentState = STATE::State::Menu;
		}
	}
	else
	{
		retry.text.color = GRAY;
	}

	Rectangle exitButt = { exit.position.x - exit.width / 2, exit.position.y - exit.height / 2, exit.width, exit.height };

	if (CheckCollisionPointRec({ cursor.positionX, cursor.positionY }, exitButt))
	{
		exit.text.color = WHITE;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			currentState = STATE::State::Exit;
		}
	}
	else
	{
		exit.text.color = GRAY;
	}
}
void GAME::ENDSCREEN::Draw(BUTTONS::Button& returnButt, BUTTONS::Button& retry, BUTTONS::Button& exit)
{
	TEXT::Text gameOver;
	gameOver.font = EXTERNS::defaultText.font;
	gameOver.color = RED;
	gameOver.fonstSize = 40;
	gameOver.posX = 50.0f;
	gameOver.posY = 20.0f;
	gameOver.text = "You lost!";

	DRAW::DrawText(gameOver);

	BUTTONS::Draw(returnButt);
	BUTTONS::Draw(retry);
	BUTTONS::Draw(exit);
}

void GAME::Deinitialize(Texture& tempTexture)
{
	UnloadSound(EXTERNS::menuSound);
	UnloadSound(EXTERNS::playSound);
	UnloadSound(EXTERNS::asteroidExplosionSound);
	UnloadSound(EXTERNS::shotgunShotSound);
	UnloadSound(EXTERNS::shootEffectSound);
	UnloadSound(EXTERNS::powerUpShotgunSound);
	UnloadSound(EXTERNS::powerUpSlowSound);
	UnloadSound(EXTERNS::powerUpInvencibleSound);
	UnloadSound(EXTERNS::bombExplosionSound);

	UnloadTexture(tempTexture);

	UnloadFont(EXTERNS::defaultText.font);

	CloseAudioDevice();
}

#pragma endregion