#include "Spaceship.h"

static float radius = 10.0f;
static float maxSpeed = 0.05f;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 240;

static int rotationDegree = 360;

void PLAYER::CreateSpaceship(Spaceship& spaceship)
{
	spaceship.position = { GLOBALS::screenWidth / 2, GLOBALS::screenHeight / 2 };
	spaceship.lookingDirection = { GetMousePosition().x, GetMousePosition().y };
	spaceship.velocity = { 0, 0 };
	spaceship.direction = { 0, 0 };

	spaceship.speed = 300.0f;

	spaceship.maxHealth = 100.0f;
	spaceship.currentHealth = 100.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

bool PLAYER::IsAccelerating()
{
	return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

void PLAYER::UpdateSpaceship(Spaceship& spaceship)
{
	spaceship.lookingDirection = { GetMousePosition().x - spaceship.position.x, GetMousePosition().y - spaceship.position.y };
	spaceship.lookingDirection = Vector2Normalize(spaceship.lookingDirection);

	if (IsAccelerating())
	{
		spaceship.direction = Vector2Subtract(GetMousePosition(), spaceship.position);
		spaceship.direction = Vector2Normalize(spaceship.direction);

		spaceship.velocity.x += spaceship.direction.x * EXTERNS::deltaT * spaceship.speed;
		spaceship.velocity.y += spaceship.direction.y * EXTERNS::deltaT * spaceship.speed;
	}
	
	spaceship.position.x += spaceship.velocity.x * EXTERNS::deltaT;
	spaceship.position.y += spaceship.velocity.y * EXTERNS::deltaT;
					
	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x) / DEG2RAD);
	spaceship.lookingDirection.x = sqrtf((spaceship.lookingDirection.x * spaceship.lookingDirection.x) + (spaceship.lookingDirection.y * spaceship.lookingDirection.y));

	#pragma region Out_Of_Bonds
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
#pragma endregion
}

void PLAYER::DrawSpaceship(Spaceship spaceship)
{
	DrawPolyLines(spaceship.position, 5, 10.0f, spaceship.lookingDirection.y, RED);
}
