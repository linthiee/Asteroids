#include "Spaceship.h"

static float radius = 10.0f;
static float maxSpeed = 200.0f;
static float defaultSpeed = 50.0f;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 240;

static int rotationDegree = 360;

void PLAYER::CreateSpaceship(Spaceship& spaceship)
{
	spaceship.position = { GLOBALS::screenWidth / 2, GLOBALS::screenHeight / 2 };
	spaceship.lookingDirection = { GetMousePosition().x, GetMousePosition().y };
	spaceship.acceleration = 50.0f;
	spaceship.maxHealth = 100.0f; 
	spaceship.currentHealth = 100.0f;
	spaceship.speed = 0.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

bool PLAYER::IsAccelerating()
{
	return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

void PLAYER::UpdateSpaceship(Spaceship& spaceship)
{
	spaceship.lookingDirection = { GetMousePosition().x - spaceship.position.x, GetMousePosition().y - spaceship.position.y };

	spaceship.direction = Vector2Normalize(spaceship.direction);
	spaceship.lookingDirection = Vector2Normalize(spaceship.lookingDirection);
	spaceship.acceleration = Normalize(spaceship.acceleration, 0.0f, 1.0f);

	if (IsAccelerating())
	{
		spaceship.direction.x += spaceship.lookingDirection.x * 0.1f;
		spaceship.direction.y += spaceship.lookingDirection.y * 0.1f;

		spaceship.speed += (spaceship.acceleration * EXTERNS::deltaT);

		if (spaceship.speed >= maxSpeed)
		{
			spaceship.speed = maxSpeed;
		}
	}
	else
	{
		spaceship.speed -= spaceship.acceleration * EXTERNS::deltaT;

		if (spaceship.speed < defaultSpeed)
		{
			spaceship.speed = defaultSpeed;
		}
	}

	spaceship.position.x += (spaceship.direction.x * EXTERNS::deltaT) * spaceship.speed;
	spaceship.position.y += (spaceship.direction.y * EXTERNS::deltaT) * spaceship.speed;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x) / DEG2RAD);
	spaceship.lookingDirection.x = sqrtf((spaceship.lookingDirection.x * spaceship.lookingDirection.x) + (spaceship.lookingDirection.y * spaceship.lookingDirection.y));

	if (spaceship.position.x > GLOBALS::screenWidth)
	{
		spaceship.position.x = 0;
	}
	if (spaceship.position.x + radius / 2 < 0)
	{
		spaceship.position.x = GLOBALS::screenWidth;
	}
	if (spaceship.position.y > GLOBALS::screenHeight)
	{
		spaceship.position.y = 0;
	}
	if (spaceship.position.y + radius / 2 < 0)
	{
		spaceship.position.y = GLOBALS::screenHeight;
	}
}

void PLAYER::DrawSpaceship(Spaceship spaceship)
{
	DrawPolyLines(spaceship.position, 5, 10.0f, spaceship.lookingDirection.y, RED);
}
