#include "PowerUp.h"

#include "Utils.h"
#include "Globals.h"
#include "Draw.h"

static float timerToSpawn = 20.0f;
static float currentSpawnTimer = 5.0f;

POWERUP::PowerUpType POWERUP::CreatePowerUp()
{
	PowerUpType result = static_cast<PowerUpType>(GetRandomValue(static_cast<int>(PowerUpType::ShotGun), static_cast<int>(PowerUpType::Slow)));

	switch (result)
	{
	case POWERUP::PowerUpType::ShotGun:

		return POWERUP::PowerUpType::ShotGun;

		break;
	case POWERUP::PowerUpType::Invincible:

		return POWERUP::PowerUpType::Invincible;

		break;
	case POWERUP::PowerUpType::Slow:

		return POWERUP::PowerUpType::Slow;

		break;
	default:

		return POWERUP::PowerUpType::Slow;

		break;
	}
}

void POWERUP::SetPowerUp(PowerUps& powerUp)
{
	if (powerUp.anyActive)
	{
		return;
	}

	currentSpawnTimer -= EXTERNS::deltaT;

	if (currentSpawnTimer <= 0.0f)
	{
		currentSpawnTimer = timerToSpawn;

		PowerUpType type = CreatePowerUp();

		switch (type)
		{
		case POWERUP::PowerUpType::ShotGun:

			powerUp.color = RED;
			powerUp.type = POWERUP::PowerUpType::ShotGun;

			break;
		case POWERUP::PowerUpType::Invincible:

			powerUp.color = WHITE;
			powerUp.type = POWERUP::PowerUpType::Invincible;

			break;
		case POWERUP::PowerUpType::Slow:

			powerUp.color = BLUE;
			powerUp.type = POWERUP::PowerUpType::Slow;

			break;
		default:
			break;
		}

		powerUp.duration = 10.0f;
		powerUp.currentDuration = 10.0f;
		powerUp.isActive = true;
		powerUp.isCollected = false;
		powerUp.position = { static_cast<float>(GetRandomValue(10, 100)), static_cast<float>(GetRandomValue(20, 100)) };
		powerUp.radius = 15.0f;
		powerUp.activeTime = 0.0f;
		powerUp.anyActive = true;

	}
}


void POWERUP::DrawPowerUp(PowerUps powerUp)
{
	if (powerUp.isActive)
	{
		DRAW::DrawSpritePro(static_cast<float>(EXTERNS::powerUpTextureID), powerUp.position.x, powerUp.position.y, powerUp.radius, powerUp.radius, powerUp.color, 260);
	}
}
