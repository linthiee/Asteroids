#include "Spaceship.h"
#include "raymath.h"
#include "Globals.h"
#include "Draw.h"

static float radius = 10.0f;
static float maxSpeed = 500.0f;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 240;

static int rotationDegree = 360;

void PLAYER::CreateSpaceship(Spaceship& spaceship)
{
	spaceship.position = { static_cast<float>(EXTERNS::screenWidth / 2), static_cast<float>(EXTERNS::screenHeight / 2) };
	spaceship.lookingDirection = { GetMousePosition().x, GetMousePosition().y };
	spaceship.velocity = { 0, 0 };
	spaceship.direction = { 0, 0 };

	spaceship.speed = 300.0f;

	spaceship.width = 100.0f;
	spaceship.height = 100.0f;

	spaceship.lives = 3;

	spaceship.fireRate = 0.2f;
	spaceship.currentFireRateCd = 0.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

bool PLAYER::IsAccelerating()
{
	return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

void PLAYER::SetLookingDirection(Spaceship& spaceship)
{
	spaceship.lookingDirection = { GetMousePosition().x - spaceship.position.x, GetMousePosition().y - spaceship.position.y };
	spaceship.lookingDirection = Vector2Normalize(spaceship.lookingDirection);
}

void PLAYER::UpdateSpaceship(Spaceship& spaceship, TEXT::Text& score)
{
	score.text = "Score: " + std::to_string(spaceship.score);

	PLAYER::SetLookingDirection(spaceship);

	if (IsAccelerating())
	{
		PLAYER::UpdateMovement(spaceship);
	}

	spaceship.currentFireRateCd -= EXTERNS::deltaT;

	PLAYER::UpdatePosition(spaceship);
	PLAYER::UpdateLookingDirection(spaceship);

	PLAYER::CheckOutOfBonds(spaceship);
}

void PLAYER::UpdateMovement(Spaceship& spaceship)
{
	spaceship.direction = Vector2Subtract(GetMousePosition(), spaceship.position);
	spaceship.direction = Vector2Normalize(spaceship.direction);

	spaceship.velocity.x += spaceship.direction.x * EXTERNS::deltaT * spaceship.speed;
	spaceship.velocity.y += spaceship.direction.y * EXTERNS::deltaT * spaceship.speed;

	float velMagnitude = Vector2Length(spaceship.velocity);

	if (velMagnitude > maxSpeed)
	{
		spaceship.velocity = Vector2Scale(Vector2Normalize(spaceship.velocity), maxSpeed);
	}
}

void PLAYER::UpdatePosition(Spaceship& spaceship)
{
	spaceship.position.x += spaceship.velocity.x * EXTERNS::deltaT;
	spaceship.position.y += spaceship.velocity.y * EXTERNS::deltaT;
}

void PLAYER::UpdateLookingDirection(Spaceship& spaceship)
{
	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x) / DEG2RAD);
	spaceship.lookingDirection.x = sqrtf((spaceship.lookingDirection.x * spaceship.lookingDirection.x) + (spaceship.lookingDirection.y * spaceship.lookingDirection.y));
}

void PLAYER::CheckOutOfBonds(Spaceship& spaceship)
{
	if (spaceship.position.x > static_cast<float>(EXTERNS::screenWidth))
	{
		spaceship.position.x = 0;
	}
	if (spaceship.position.x + radius / 2 < 0)
	{
		spaceship.position.x = static_cast<float>(EXTERNS::screenWidth);
	}
	if (spaceship.position.y > static_cast<float>(EXTERNS::screenHeight))
	{
		spaceship.position.y = 0;
	}
	if (spaceship.position.y + radius / 2 < 0)
	{
		spaceship.position.y = static_cast<float>(EXTERNS::screenHeight);
	}
}

void PLAYER::UpdateLives(Spaceship& spaceship)
{
	spaceship.lives--;
}

void PLAYER::ResetSpaceship(Spaceship& spaceship)
{
	spaceship.position = { static_cast<float>(EXTERNS::screenWidth / 2), static_cast<float>(EXTERNS::screenHeight / 2) };
	spaceship.lookingDirection = { GetMousePosition().x, GetMousePosition().y };
	spaceship.velocity = { 0, 0 };
	spaceship.direction = { 0, 0 };

	spaceship.speed = 300.0f;

	spaceship.fireRate = 0.2f;
	spaceship.currentFireRateCd = 0.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

void PLAYER::DrawSpaceship(Spaceship spaceship)
{
	spaceship.lookingDirection.y += 90.0f;
	DRAW::DrawSpritePro(static_cast<float>(spaceship.textureID), spaceship.position.x, spaceship.position.y, spaceship.width, spaceship.height, WHITE, spaceship.lookingDirection.y);
}

void PLAYER::DrawLives(Spaceship spaceship)
{
	for (int i = 0; i < spaceship.lives; i++)
	{
		DRAW::DrawSprite(static_cast<float>(spaceship.textureID), spaceship.width / 7 - (5.0f * i), 3.0f, 6.0f, 6.0f, WHITE);
	}
}
