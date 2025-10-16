#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Globals.h"

namespace ASTEROIDS
{
	enum class AsteroidType
	{
		Small = 1, Medium = 2, Large = 4,
	};

	struct Asteroid
	{
		bool isActive;

		Vector2 position;
		Vector2 velocity;
	
		float rotation;
		float speed;

		int textureID;

		AsteroidType type;
	};

	void CreateAsteroid(ASTEROIDS::Asteroid& asteroid);
	void UpdateAsteroid(ASTEROIDS::Asteroid& asteroid);
}