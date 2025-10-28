#include "PowerUp.h"
#include "Utils.h"
#include "Globals.h"

#include <iostream>

static float min = 0.0f;
static float max = 100.0f;

//static float shotGunPU = 70.0f;
//static float slowPU = 50.0f;
//static float invinciblePU = 80.0f;

static float timerToSpawn = 20.0f;
static float currentSpawnTimer = 5.0f;

POWERUP::PowerUpType POWERUP::CreatePowerUp()
{
	//float result = static_cast<float>(GetRandomValue(static_cast<int>(min), static_cast<int>(max)));

	//if (result >= invinciblePU)
	//{
	//	return POWERUP::PowerUpType::Invincible;
	//}
	//else if (result >= shotGunPU)
	//{
	//	return POWERUP::PowerUpType::ShotGun;
	//}
	//else
	//{
	//	return POWERUP::PowerUpType::Slow;
	//}

	return POWERUP::PowerUpType::Invincible;
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

			powerUp.type = POWERUP::PowerUpType::ShotGun;

			break;
		case POWERUP::PowerUpType::Invincible:

			powerUp.type = POWERUP::PowerUpType::Invincible;

			break;
		case POWERUP::PowerUpType::Slow:

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
		powerUp.radius = 5.0f;
		powerUp.activeTime = 0.0f;
		powerUp.anyActive = true;

	}
	std::cout << static_cast<int>(currentSpawnTimer) << "\r" << "  ,   " << static_cast<int>(powerUp.activeTime) << "\r";
}


void POWERUP::DrawPowerUp(PowerUps powerUp)
{
	powerUp.position.x = UTILS::PercentToPixelsX(powerUp.position.x);
	powerUp.position.y = UTILS::PercentToPixelsY(powerUp.position.y);

	DrawCircle(static_cast<int>(powerUp.position.x), static_cast<int>(powerUp.position.y), powerUp.radius, RED);
}
