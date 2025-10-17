#include <iostream>
#include "Spaceship.h"

static int minRotationSpeed = 5;
static int maxRotationSpeed = 240;

static int rotationDegree = 360;

void PLAYER::CreateSpaceship(Spaceship& spaceship)
{
	spaceship.position = { GLOBALS::screenWidth / 2, GLOBALS::screenHeight / 2 };
	spaceship.lookingDirection = { GetMousePosition().x, GetMousePosition().y};

	spaceship.maxHealth = 100.0f;
	spaceship.currentHealth = 100.0f;
	spaceship.speed = 30.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f( spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

void PLAYER::UpdateSpaceship(Spaceship& spaceship)
{
	spaceship.lookingDirection = { GetMousePosition().x - spaceship.position.x, GetMousePosition().y - spaceship.position.y };

	//if(apretando mouse)
	{
		spaceship.direction.x = spaceship.lookingDirection.x;
		spaceship.direction.y = spaceship.lookingDirection.y;

	}
	spaceship.direction = Vector2Normalize(spaceship.direction);
	
	spaceship.position.x += spaceship.direction.x * GetFrameTime() * spaceship.speed;
	spaceship.position.y += spaceship.direction.y * GetFrameTime() * spaceship.speed;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x) / DEG2RAD);
	spaceship.lookingDirection.x = sqrt((spaceship.lookingDirection.x * spaceship.lookingDirection.x) + (spaceship.lookingDirection.y * spaceship.lookingDirection.y));

	std::cout << spaceship.lookingDirection.x << " , " << spaceship.lookingDirection.y << "\n";
}

void PLAYER::DrawSpaceship(Spaceship spaceship)
{
	DrawPolyLines(spaceship.position, 5, 10.0f, spaceship.lookingDirection.y, RED);
}
