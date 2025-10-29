#pragma once
#include <string>
#include "Text.h"

namespace EXTERNS
{
	extern int screenWidth;
	extern int screenHeight;
	extern float deltaT;

	extern std::string spaceshipTexture;
	extern int spaceshipTextureID;

	extern std::string bigAsteroidTexture;
	extern int bigAsteroidTextureID;

	extern std::string mediumAsteroidTexture;
	extern int mediumAsteroidTextureID;

	extern std::string smallAsteroidTexture;
	extern int smallAsteroidTextureID;

	extern std::string firstFrameLaserTexture;
	extern int firstFrameLaserTextureID;

	extern std::string bombTexture;
	extern int bombTextureID;

	extern std::string backgroundTexture;
	extern int backgroundTextureID;

	extern std::string menuTexture;
	extern int menuTextureID;

	extern std::string buttonTexture;
	extern int buttonTextureID;

	extern std::string titleTexture;
	extern int titleTextureID;

	extern std::string gameHUD;
	extern int gameHudID;

	extern std::string powerUpTexture;
	extern int powerUpTextureID;

	extern std::string explosionTexture;

	extern std::string fontText;
	extern int font;

	extern TEXT::Text defaultText;

	extern std::string shootEffect;
	extern Sound shootEffectSound;

	extern std::string asteroidExplosion;
	extern Sound asteroidExplosionSound;

	extern std::string shotgunShot;
	extern Sound shotgunShotSound;

	extern std::string powerUpShotgun;
	extern Sound powerUpShotgunSound;

	extern std::string powerUpSlow;
	extern Sound powerUpSlowSound;

	extern std::string powerUpInvencible;
	extern Sound powerUpInvencibleSound;

	extern std::string bombExplosion;
	extern Sound bombExplosionSound;

	extern std::string menuSong;
	extern Sound menuSound;

	extern std::string playSong;
	extern Sound playSound;

	extern double timer;

	extern int initialMaxAsteroidsOnScreen;  
	extern int maxAsteroidsOnScreen;
	extern float spawnTime;       
	extern float timerSpawn;
	extern float timerToIncreaseDifficulty; 
	extern float difficultyTimer;

	extern int currentAsteroids;

	extern int spawnInvincibilityTimer;
	extern int spawnInvincibilityTimerDecay;

	extern bool retry;

	extern bool gamePaused;
}

namespace GLOBALS
{
	const int maxAsteroids = 100;

	const int asteroidDiversity = 3;

	const int maxLives = 3;

	const int maxExplosions = 100;
}