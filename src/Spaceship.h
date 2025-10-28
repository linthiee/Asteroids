#pragma once
#include "raylib.h"
#include "PowerUp.h"
#include "Text.h"

namespace PLAYER
{
	struct Spaceship
	{
		POWERUP::PowerUps powerUp;

		Color color;

		Texture texture;
		int textureID;

		Vector2 direction;
		Vector2 lookingDirection;
		Vector2 position;
		Vector2 velocity;
		Vector2 lastValidAimDir;

		bool isShotgunActive;
		bool isInvincible;
		bool hasSlow;

		bool onSpawnInvincibility;

		float onSpawnUnvincibleTimer;

		float speed;

		float width;
		float height;

		int lives;
		int score;

		float radius;

		float fireRate;
		float currentFireRateCd;
	};

	void CreateSpaceship(Spaceship& spaceship);

	bool HasLost(Spaceship spaceship);
	void SetLife(Spaceship& spaceship);

	bool IsAccelerating();
	void SetLookingDirection(Spaceship& spaceship);
	void UpdateSpaceship(Spaceship& spaceship, TEXT::Text& score);
	void UpdateMovement(Spaceship& spaceship);
	void UpdatePosition(Spaceship& spaceship);
	void UpdateLookingDirection(Spaceship& spaceship);
	void CheckOutOfBonds(Spaceship& spaceship);

	void UpdateInvencibility(Spaceship& spaceship);

	void UpdateLives(Spaceship& spaceship);
	void ResetSpaceship(Spaceship& spaceship);

	bool CollectedPowerUp(Spaceship spaceship);
	void ApplyPowerUp(Spaceship& spaceship);

	void UpdatePowerUp(Spaceship& spaceship);

	void DrawSpaceship(Spaceship spaceship);
	void DrawLives(Spaceship spaceship);
}