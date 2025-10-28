#include "Spaceship.h"
#include "raymath.h"
#include "Globals.h"
#include "Draw.h"
#include "Utils.h"

static float radius = 10.0f;
static float maxSpeed = 500.0f;

static int minRotationSpeed = 5;
static int maxRotationSpeed = 240;

static int rotationDegree = 360;

static float timerToDespawn = 15.0f;

static Vector2 mousePercent = { 0, 0 };

void PLAYER::CreateSpaceship(Spaceship& spaceship)
{
	spaceship.position = { 50.0f, 50.0f };

	mousePercent = { UTILS::PixelsToPercentX(GetMousePosition().x), UTILS::PixelsToPercentY(GetMousePosition().y) };
	spaceship.lookingDirection = { mousePercent.x, mousePercent.y };

	spaceship.velocity = { 0, 0 };
	spaceship.direction = { 0, 0 };

	spaceship.speed = 300.0f;

	spaceship.color = WHITE;

	spaceship.isShotgunActive = false;
	spaceship.isInvincible = false;
	spaceship.hasSlow = false;

	spaceship.width = 100.0f;
	spaceship.height = 100.0f;

	spaceship.lives = 3;

	spaceship.radius = 20.0f;

	spaceship.fireRate = 0.4f;
	spaceship.currentFireRateCd = 0.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

bool PLAYER::IsAccelerating()
{
	return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

void PLAYER::SetLookingDirection(Spaceship& spaceship)
{
	spaceship.lookingDirection = { mousePercent.x - spaceship.position.x, mousePercent.y - spaceship.position.y };
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
	spaceship.direction = Vector2Subtract(mousePercent, spaceship.position);
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
	spaceship.position.x += (spaceship.velocity.x / EXTERNS::screenWidth) * 100.0f * EXTERNS::deltaT;
	spaceship.position.y += (spaceship.velocity.y / EXTERNS::screenHeight) * 100.0f * EXTERNS::deltaT;
}

void PLAYER::UpdateLookingDirection(Spaceship& spaceship)
{
	mousePercent = { UTILS::PixelsToPercentX(GetMousePosition().x), UTILS::PixelsToPercentY(GetMousePosition().y) };

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x) / DEG2RAD);
	spaceship.lookingDirection.x = sqrtf((spaceship.lookingDirection.x * spaceship.lookingDirection.x) + (spaceship.lookingDirection.y * spaceship.lookingDirection.y));
}

void PLAYER::CheckOutOfBonds(Spaceship& spaceship)
{
	float pixelRadius = spaceship.radius;

	float radiusPercentX = UTILS::PixelsToPercentX(pixelRadius);
	float radiusPercentY = UTILS::PixelsToPercentY(pixelRadius);

	if (spaceship.position.x - radiusPercentX > 100.0f)
	{
		spaceship.position.x = 0.0f - radiusPercentX;
	}
	if (spaceship.position.x + radiusPercentX < 0.0f)
	{
		spaceship.position.x = 100.0f + radiusPercentX;
	}
	if (spaceship.position.y - radiusPercentY > 100.0f)
	{
		spaceship.position.y = 0.0f - radiusPercentY;
	}
	if (spaceship.position.y + radiusPercentY < 0.0f)
	{
		spaceship.position.y = 100.0f + radiusPercentY;
	}
}

void PLAYER::UpdateLives(Spaceship& spaceship)
{
	spaceship.lives--;
}

void PLAYER::ResetSpaceship(Spaceship& spaceship)
{
	spaceship.position = { 50.0f, 50.0f };

	mousePercent = { (GetMousePosition().x / EXTERNS::screenWidth) * 100.0f, (GetMousePosition().y / EXTERNS::screenHeight) * 100.0f };

	spaceship.lookingDirection = { mousePercent.x, mousePercent.y };
	spaceship.velocity = { 0, 0 };
	spaceship.direction = { 0, 0 };

	spaceship.color = WHITE;

	spaceship.isShotgunActive = false;
	spaceship.isInvincible = false;
	spaceship.hasSlow = false;

	spaceship.speed = 300.0f;

	spaceship.fireRate = 0.4f;
	spaceship.currentFireRateCd = 0.0f;

	spaceship.lookingDirection.y = static_cast<float>(atan2f(spaceship.lookingDirection.y, spaceship.lookingDirection.x));
}

bool PLAYER::CollectedPowerUp(Spaceship spaceship)
{
	float spaceshipPixelX = UTILS::PercentToPixelsX(spaceship.position.x);
	float spaceshipPixelY = UTILS::PercentToPixelsY(spaceship.position.y);
	float powerUpPixelX = UTILS::PercentToPixelsX(spaceship.powerUp.position.x);
	float powerUpPixelY = UTILS::PercentToPixelsY(spaceship.powerUp.position.y);

	float distX = spaceshipPixelX - powerUpPixelX;
	float distY = spaceshipPixelY - powerUpPixelY;
	float distanceSquared = (distX * distX) + (distY * distY);

	float powerUpRadius = spaceship.powerUp.radius;
	float spaceshipRadius = spaceship.radius;

	float sumOfRadius = spaceshipRadius + powerUpRadius;
	float sumOfRadiusSquared = sumOfRadius * sumOfRadius;

	return distanceSquared <= sumOfRadiusSquared;
}

void PLAYER::ApplyPowerUp(Spaceship& spaceship)
{
	if (CollectedPowerUp(spaceship))
	{

		if (spaceship.powerUp.isActive && !spaceship.powerUp.isCollected && CollectedPowerUp(spaceship))
		{
			spaceship.powerUp.isCollected = true;

			switch (spaceship.powerUp.type)
			{
			case POWERUP::PowerUpType::ShotGun:

				SetSoundVolume(EXTERNS::powerUpShotgunSound, 0.5);
				PlaySound(EXTERNS::powerUpShotgunSound);
				spaceship.isShotgunActive = true;

				break;

			case POWERUP::PowerUpType::Invincible:

				SetSoundVolume(EXTERNS::powerUpInvencibleSound, 0.5);
				PlaySound(EXTERNS::powerUpInvencibleSound);
				spaceship.isInvincible = true;
				spaceship.color = GOLD;

				break;

			case POWERUP::PowerUpType::Slow:

				SetSoundVolume(EXTERNS::powerUpSlowSound, 0.5);
				PlaySound(EXTERNS::powerUpSlowSound);
				spaceship.hasSlow = true;

				break;
			}
		}
	}
}

void PLAYER::UpdatePowerUp(Spaceship& spaceship)
{
	if (!spaceship.powerUp.anyActive)
	{
		return;
	}

	if (spaceship.powerUp.isActive && !spaceship.powerUp.isCollected)
	{
		spaceship.powerUp.activeTime += EXTERNS::deltaT;

		if (spaceship.powerUp.activeTime >= timerToDespawn)
		{
			spaceship.powerUp.isActive = false;
			spaceship.powerUp.anyActive = false;
			spaceship.powerUp.activeTime = 0.0f;
		}
	}

	if (spaceship.powerUp.isCollected)
	{
		spaceship.powerUp.currentDuration -= EXTERNS::deltaT;

		if (spaceship.powerUp.currentDuration <= 0.0f)
		{
			spaceship.powerUp.isActive = false;
			spaceship.powerUp.anyActive = false;
			spaceship.powerUp.currentDuration = spaceship.powerUp.duration;

			switch (spaceship.powerUp.type)
			{
			case POWERUP::PowerUpType::ShotGun:

				spaceship.isShotgunActive = false;

				break;

			case POWERUP::PowerUpType::Invincible:

				spaceship.color = WHITE;
				spaceship.isInvincible = false;

				break;

			case POWERUP::PowerUpType::Slow:

				spaceship.hasSlow = false;

				break;
			}

		}
	}
}
void PLAYER::DrawSpaceship(Spaceship spaceship)
{
	float width = UTILS::PixelsToPercentX(static_cast<float>(spaceship.width));
	float height = UTILS::PixelsToPercentY(static_cast<float>(spaceship.height));

	spaceship.lookingDirection.y += 90.0f;
	DRAW::DrawSpritePro(static_cast<float>(spaceship.textureID), spaceship.position.x, spaceship.position.y, width, height, spaceship.color, spaceship.lookingDirection.y);
}

void PLAYER::DrawLives(Spaceship spaceship)
{
	for (int i = 0; i < spaceship.lives; i++)
	{
		DRAW::DrawSprite(static_cast<float>(spaceship.textureID), spaceship.width / 8 - (4.0f * i), 2.0f, 5.0f, 5.0f, WHITE);
	}
}
