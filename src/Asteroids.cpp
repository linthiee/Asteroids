#include "Asteroids.h"

static int radius = 10;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 120;

static int rotationDegree = 360;

static float baseSpeed = 0.0f;

static int minSpeed = 5;
static int maxSpeed = 7;

void ASTEROIDS::CreateAsteroid(Asteroid& asteroid)
{
	baseSpeed = static_cast<float>(GetRandomValue(minSpeed, maxSpeed));

	asteroid.type = AsteroidType::Large;
	//asteroid.type = static_cast<AsteroidType>(GetRandomValue(static_cast<int>(AsteroidType::Small), static_cast<int>(AsteroidType::Large)));

	float speedFactor = ((1.0f / static_cast<float>(asteroid.type)) * baseSpeed);

	asteroid.isActive = true;

	asteroid.position.x = static_cast<float>(GetRandomValue(0, GLOBALS::screenWidth));
	asteroid.position.y = static_cast<float>(GetRandomValue(0, GLOBALS::screenHeight));

	asteroid.velocity = { baseSpeed * speedFactor , baseSpeed * speedFactor };

	asteroid.rotation = static_cast<float>((GetRandomValue(0, rotationDegree) * DEG2RAD));

	asteroid.velocity.x = cosf(asteroid.rotation) * asteroid.velocity.x;
	asteroid.velocity.y = sinf(asteroid.rotation) * asteroid.velocity.y;

	asteroid.speed = static_cast<float>(GetRandomValue(minRotationSpeed, maxRotationSpeed));
}

void ASTEROIDS::UpdateAsteroid(Asteroid& asteroid)
{
	asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, EXTERNS::deltaT));
	asteroid.rotation += asteroid.speed * EXTERNS::deltaT;

#pragma region Check_If_Is_Out_Of_Bonds

	if (asteroid.position.x - static_cast<float>(radius * static_cast<int>(asteroid.type)) > GLOBALS::screenWidth)
	{
		asteroid.position.x = 0;
	}
	if (asteroid.position.x + static_cast<float>(radius * static_cast<int>(asteroid.type)) < 0)
	{
		asteroid.position.x = GLOBALS::screenWidth - static_cast<float>(radius / 2 * static_cast<int>(asteroid.type));
	}
	if (asteroid.position.y - static_cast<float>(radius * static_cast<int>(asteroid.type)) > GLOBALS::screenHeight)
	{
		asteroid.position.y = 0;
	}
	if (asteroid.position.y + static_cast<float>(radius * static_cast<int>(asteroid.type)) < 0)
	{
		asteroid.position.y = GLOBALS::screenHeight;
	}

#pragma endregion
}

void ASTEROIDS::DrawAsteroid(Asteroid& asteroid)
{
	DrawPolyLines(asteroid.position, 3, static_cast<float>(radius * static_cast<int>(asteroid.type)), asteroid.rotation, WHITE);
}
