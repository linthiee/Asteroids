#include "Asteroids.h"

static int minRotationSpeed = 5;
static int maxRotationSpeed = 250;

static int rotationDegree = 360;

static float baseSpeed = 5.0f;

void ASTEROIDS::CreateAsteroid(ASTEROIDS::Asteroid& asteroid)
{
	asteroid.isActive = true;

	asteroid.position.x = GetRandomValue(0, GetScreenWidth());
	asteroid.position.y = GetRandomValue(0, GetScreenHeight());
	
	asteroid.type = ASTEROIDS::AsteroidType::Large;
	asteroid.velocity = { baseSpeed * 1.0f / static_cast<float>(asteroid.type) * 0.6f + 0.5f , baseSpeed * 1.0f / static_cast<float>(asteroid.type) * 0.6f + 0.5f };

	asteroid.rotation = GetRandomValue(0, rotationDegree);
	asteroid.speed = GetRandomValue(minRotationSpeed, maxRotationSpeed);
}

void ASTEROIDS::UpdateAsteroid(ASTEROIDS::Asteroid& asteroid)
{
	asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, deltaT));

	asteroid.rotation += asteroid.speed * deltaT;
}