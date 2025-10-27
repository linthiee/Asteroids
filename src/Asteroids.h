#pragma once
#include "raylib.h"
#include "Bullets.h"
#include "Globals.h" 

namespace ASTEROIDS
{
	enum class AsteroidType
	{
		Small = 1, Medium = 2, Large = 3,
	};

	enum class AsteroidSize
	{
		Small = 2, Medium = 4, Large = 6,
	};

	struct Asteroid
	{
		bool isActive;

		Texture textures;

		Vector2 position;
		Vector2 velocity;
	
		float rotation;
		float speed;

		int size;
		int score;

		int textureID;

		AsteroidType type;
	};

	void CreateAsteroid(Asteroid& asteroid);

	void UpdateAsteroid(Asteroid& asteroid);
	void UpdateMovement(Asteroid& asteroid);
	void CheckOutOfBonds(Asteroid& asteroid);

	bool HasCollided(BULLETS::Bullets& bullet, Asteroid& asteroid);
	bool HasCollided(PLAYER::Spaceship spacehsip, Asteroid asteroid);

	void SplitAsteroid(Asteroid& asteroid, Asteroid allAsteroids[GLOBALS::maxAsteroids]);

	void DrawAsteroid(Asteroid& asteroid);
}