#include <iostream>
#include "Asteroids.h"
#include "raymath.h"
#include "Draw.h"
#include "Utils.h"

static int radius = 10;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 120;

static int rotationDegree = 360;

static float baseSpeed = 0.0f;

static int minSpeed = 5;
static int maxSpeed = 7;

static int asteroidsToDivide = 2;

void ASTEROIDS::CreateAsteroid(Asteroid& asteroid)
{
	int scores[GLOBALS::asteroidDiversity] = { 100, 250, 350 };

	baseSpeed = static_cast<float>(GetRandomValue(minSpeed, maxSpeed));

	//asteroid.type = AsteroidType::Large;
	asteroid.type = static_cast<AsteroidType>(GetRandomValue(static_cast<int>(AsteroidType::Small), static_cast<int>(AsteroidType::Large)));

	asteroid.radius = 5.0f;

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

	asteroid.position.x = static_cast<float>(GetRandomValue(0, 100));
	asteroid.position.y = static_cast<float>(GetRandomValue(0, 100));

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
	Vector2 velocityPercent = { (asteroid.velocity.x / EXTERNS::screenWidth) * 100.0f, (asteroid.velocity.y / EXTERNS::screenHeight) * 100.0f };

	asteroid.position = Vector2Add(asteroid.position, Vector2Scale(velocityPercent, EXTERNS::deltaT));
	asteroid.rotation += asteroid.speed * EXTERNS::deltaT;
}

void ASTEROIDS::CheckOutOfBonds(Asteroid& asteroid)
{
	float pixelRadius = static_cast<float>(radius * static_cast<int>(asteroid.type));

	float radiusPercentX = UTILS::PixelsToPercentX(pixelRadius);
	float radiusPercentY = UTILS::PixelsToPercentY(pixelRadius);

	if (asteroid.position.x - radiusPercentX > 100.0f)
	{
		asteroid.position.x = 0.0f - radiusPercentX; 
	}
	if (asteroid.position.x + radiusPercentX < 0.0f)
	{
		asteroid.position.x = 100.0f + radiusPercentX; 
	}
	if (asteroid.position.y - radiusPercentY > 100.0f)
	{
		asteroid.position.y = 0.0f - radiusPercentY;
	}
	if (asteroid.position.y + radiusPercentY < 0.0f)
	{
		asteroid.position.y = 100.0f + radiusPercentY;
	}
}

bool ASTEROIDS::HasCollided(BULLETS::Bullets& bullet, Asteroid& asteroid)
{
	float bulletPixelX = UTILS::PercentToPixelsX(bullet.position.x);
	float bulletPixelY = UTILS::PercentToPixelsY(bullet.position.y);
	float asteroidPixelX = UTILS::PercentToPixelsX(asteroid.position.x);
	float asteroidPixelY = UTILS::PercentToPixelsY(asteroid.position.y);

	float distX = bulletPixelX - asteroidPixelX;
	float distY = bulletPixelY - asteroidPixelY;
	float distanceSquared = (distX * distX) + (distY * distY);

	float asteroidRadius = static_cast<float>(radius * static_cast<int>(asteroid.size));
	float bulletRadius = bullet.radius;

	float sumOfRadius = asteroidRadius + bulletRadius;
	float sumOfRadiusSquared = sumOfRadius * sumOfRadius;

	return distanceSquared <= sumOfRadiusSquared;
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

	if (asteroid.type == AsteroidType::Large)
	{
		newType = AsteroidType::Medium;
		newSize = AsteroidSize::Medium;
		newTextureID = EXTERNS::mediumAsteroidTextureID;
	}
	else
	{
		newType = AsteroidType::Small;
		newSize = AsteroidSize::Small;
		newTextureID = EXTERNS::smallAsteroidTextureID;
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

		if (asteroidsSpawmed >= asteroidsToDivide)
		{
			break;
		}
	}
}

void ASTEROIDS::DrawAsteroid(Asteroid& asteroid)
{
	float width = UTILS::PixelsToPercentX(static_cast<float>(radius * static_cast<int>(asteroid.size)) * 5.0f);
	float height = UTILS::PixelsToPercentY(static_cast<float>(radius * static_cast<int>(asteroid.size)) * 4.0f);

	DRAW::DrawSpritePro(static_cast<float>(asteroid.textureID), asteroid.position.x, asteroid.position.y, width,
		height, WHITE, asteroid.rotation);

}
