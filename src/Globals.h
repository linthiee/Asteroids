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

	extern double timer;

	extern int initialMaxAsteroidsOnScreen;  
	extern int maxAsteroidsOnScreen;
	extern float spawnTime;       
	extern float timerSpawn;
	extern float timerToIncreaseDifficulty; 
	extern float difficultyTimer;
}

namespace GLOBALS
{
	const int maxAsteroids = 100;

	const int asteroidDiversity = 3;

	const int maxLives = 3;

	const int maxExplosions = 100;
}