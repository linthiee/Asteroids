#pragma once
#include "raylib.h"

namespace POWERUP
{
	enum class PowerUpType
	{
		ShotGun, Invincible, Slow
	};

	struct PowerUps
	{
		PowerUpType type;

		bool isActive;
		bool isCollected;
		bool anyActive;

		Color color;

		Vector2 position;

		float duration;
		float currentDuration;

		float activeTime;

		float radius;
	};

	PowerUpType CreatePowerUp();

	void SetPowerUp(PowerUps& powerUp);

	void DrawPowerUp(PowerUps powerUp);
}