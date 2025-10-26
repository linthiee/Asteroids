#pragma once
#include <string>

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
}

namespace GLOBALS
{
	const int maxAsteroids = 10;

	const int asteroidDiversity = 3;
}