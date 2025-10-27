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

	extern std::string fontText;
	extern int font;

	extern TEXT::Text defaultText;

	extern std::string shootEffect;
	extern Sound shootEffectSound;
}

namespace GLOBALS
{
	const int maxAsteroids = 100;

	const int asteroidDiversity = 3;

	const int maxLives = 3;
}