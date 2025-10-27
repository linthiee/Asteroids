#include <iostream>
#include "Asteroids.h"
#include "raymath.h"
#include "Draw.h"

static int radius = 10;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 120;

static int rotationDegree = 360;

static float baseSpeed = 0.0f;

static int minSpeed = 5;
static int maxSpeed = 7;

void ASTEROIDS::CreateAsteroid(Asteroid& asteroid)
{
	int scores[GLOBALS::asteroidDiversity] = { 100, 250, 350 };

	baseSpeed = static_cast<float>(GetRandomValue(minSpeed, maxSpeed));

	//asteroid.type = AsteroidType::Large;
	asteroid.type = static_cast<AsteroidType>(GetRandomValue(static_cast<int>(AsteroidType::Small), static_cast<int>(AsteroidType::Large)));

	switch (asteroid.type)
	{
	case AsteroidType::Large:

		asteroid.textureID = EXTERNS::bigAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Large);
		asteroid.score = scores[static_cast<int>(AsteroidType::Large) - 1];

		break;

	case AsteroidType::Medium:

		asteroid.textureID = EXTERNS::mediumAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Medium);
		asteroid.score = scores[static_cast<int>(AsteroidType::Medium) - 1];

		break;

	case AsteroidType::Small:

		asteroid.textureID = EXTERNS::smallAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Small);
		asteroid.score = scores[static_cast<int>(AsteroidType::Small) - 1];

		break;

	default:

		std::cout << "Unable to assign a texture to the asteroid\n";

		break;
	}

	float speedFactor = ((1.0f / static_cast<float>(asteroid.type)) * baseSpeed);

	asteroid.isActive = true;

	asteroid.position.x = static_cast<float>(GetRandomValue(0, EXTERNS::screenWidth));
	asteroid.position.y = static_cast<float>(GetRandomValue(0, EXTERNS::screenHeight));

	asteroid.velocity = { baseSpeed * speedFactor , baseSpeed * speedFactor };

	asteroid.rotation = static_cast<float>((GetRandomValue(0, rotationDegree) * DEG2RAD));

	asteroid.velocity.x = cosf(asteroid.rotation) * asteroid.velocity.x;
	asteroid.velocity.y = sinf(asteroid.rotation) * asteroid.velocity.y;

	asteroid.speed = static_cast<float>(GetRandomValue(minRotationSpeed, maxRotationSpeed));
}

void ASTEROIDS::UpdateAsteroid(Asteroid& asteroid)
{
	ASTEROIDS::UpdateMovement(asteroid);
	ASTEROIDS::CheckOutOfBonds(asteroid);
}

void ASTEROIDS::UpdateMovement(Asteroid& asteroid)
{
	asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, EXTERNS::deltaT));
	asteroid.rotation += asteroid.speed * EXTERNS::deltaT;
}

void ASTEROIDS::CheckOutOfBonds(Asteroid& asteroid)
{
	if (asteroid.position.x - static_cast<float>(radius * static_cast<int>(asteroid.type)) > EXTERNS::screenWidth)
	{
		asteroid.position.x = 0;
	}
	if (asteroid.position.x + static_cast<float>(radius * static_cast<int>(asteroid.type)) < 0)
	{
		asteroid.position.x = EXTERNS::screenWidth - static_cast<float>(radius / 2 * static_cast<int>(asteroid.type));
	}
	if (asteroid.position.y - static_cast<float>(radius * static_cast<int>(asteroid.type)) > EXTERNS::screenHeight)
	{
		asteroid.position.y = 0;
	}
	if (asteroid.position.y + static_cast<float>(radius * static_cast<int>(asteroid.type)) < 0)
	{
		asteroid.position.y = static_cast<float>(EXTERNS::screenHeight);
	}
}

bool ASTEROIDS::HasCollided(BULLETS::Bullets& bullet, Asteroid& asteroid)
{
	float distX = asteroid.position.x - bullet.position.x;
	float distY = asteroid.position.y - bullet.position.y;

	float distance = (distX * distX) + (distY * distY);

	float asteroidRadius = static_cast<float>(radius * static_cast<int>(asteroid.size));
	float bulletRadius = sqrtf(bullet.width + bullet.height) * 0.5f;
	float sum = asteroidRadius + bulletRadius;

	return distance <= (sum * sum);
}

bool ASTEROIDS::HasCollided(PLAYER::Spaceship spacehsip, Asteroid asteroid)
{
	float distX = spacehsip.position.x - asteroid.position.x;
	float distY = spacehsip.position.y - asteroid.position.y;

	float distance = (distX * distX) + (distY * distY);

	float asteroidRadius = static_cast<float>(radius * static_cast<int>(asteroid.size));
	float spaceshipRadius = sqrtf(spacehsip.width + spacehsip.height) * 2.0f;
	float sum = asteroidRadius + spaceshipRadius;

	DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroidRadius, RED);
	DrawCircle(static_cast<int>(spacehsip.position.x), static_cast<int>(spacehsip.position.y), spaceshipRadius, GREEN);

	return distance <= (sum * sum);
}


void ASTEROIDS::SplitAsteroid(Asteroid& asteroid, Asteroid allAsteroids[GLOBALS::maxAsteroids])
{
	if (asteroid.type == AsteroidType::Small)
	{
		return;
	}

	AsteroidType newType;
	AsteroidSize newSize;
	int newTextureID;
	int asteroidsToCreate;

	if (asteroid.type == AsteroidType::Large)
	{
		newType = AsteroidType::Medium;
		newSize = AsteroidSize::Medium;
		newTextureID = EXTERNS::mediumAsteroidTextureID;
		asteroidsToCreate = 2;
	}
	else
	{
		newType = AsteroidType::Small;
		newSize = AsteroidSize::Small;
		newTextureID = EXTERNS::smallAsteroidTextureID;
		asteroidsToCreate = 4;
	}

	int asteroidsSpawmed = 0;
	for (int i = 0; i < GLOBALS::maxAsteroids; i++)
	{
		if (!allAsteroids[i].isActive)
		{
			Asteroid& splited = allAsteroids[i];

			splited.isActive = true;
			splited.position = asteroid.position;
			splited.type = newType;
			splited.size = static_cast<int>(newSize);
			splited.textureID = newTextureID;

			float newBaseSpeed = static_cast<float>(GetRandomValue(minSpeed, maxSpeed));
			float speedFactor = ((1.0f / static_cast<float>(splited.type)) * newBaseSpeed);

			splited.velocity = { newBaseSpeed * speedFactor, newBaseSpeed * speedFactor };

			splited.rotation = static_cast<float>((GetRandomValue(0, rotationDegree) * DEG2RAD));

			splited.velocity.x = cosf(splited.rotation) * splited.velocity.x;
			splited.velocity.y = sinf(splited.rotation) * splited.velocity.y;

			splited.speed = static_cast<float>(GetRandomValue(minRotationSpeed, maxRotationSpeed));

			asteroidsSpawmed++;
		}

		if (asteroidsSpawmed >= asteroidsToCreate)
		{
			break;
		}
	}
}

void ASTEROIDS::DrawAsteroid(Asteroid& asteroid)
{
	DRAW::DrawSpritePro(static_cast<float>(asteroid.textureID), asteroid.position.x, asteroid.position.y,
		static_cast<float>(radius * static_cast<int>(asteroid.size)) * 5.0f, static_cast<float>(radius * static_cast<int>(asteroid.size)) * 4.0f, WHITE, asteroid.rotation);
}
