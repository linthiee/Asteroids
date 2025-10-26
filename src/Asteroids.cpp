#include <iostream>
#include "Asteroids.h"
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
	baseSpeed = static_cast<float>(GetRandomValue(minSpeed, maxSpeed));

	//asteroid.type = AsteroidType::Large;
	asteroid.type = static_cast<AsteroidType>(GetRandomValue(static_cast<int>(AsteroidType::Small), static_cast<int>(AsteroidType::Large)));

	switch (asteroid.type)
	{
	case AsteroidType::Large:
		
		asteroid.textureID = EXTERNS::bigAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Large);

		break;

	case AsteroidType::Medium:
		
		asteroid.textureID = EXTERNS::mediumAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Medium);

		break;

	case AsteroidType::Small:
		
		asteroid.textureID = EXTERNS::smallAsteroidTextureID;
		asteroid.size = static_cast<int>(AsteroidSize::Small);

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

void ASTEROIDS::DrawAsteroid(Asteroid& asteroid)
{
	DRAW::DrawSpritePro(static_cast<float>(asteroid.textureID), asteroid.position.x, asteroid.position.y,
		static_cast<float>(radius * static_cast<int>(asteroid.size)) * 5.0f, static_cast<float>(radius * static_cast<int>(asteroid.size)) * 4.0f, WHITE, asteroid.rotation);
}
