#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Globals.h"

namespace PLAYER
{
	struct Spaceship
	{
		Texture texture;
		int textureID;

		Vector2 direction;
		Vector2 lookingDirection;
		Vector2 position;
		Vector2 velocity;
		Vector2 lastValidAimDir;

		float speed;

		float width;
		float height;

		float maxHealth;
		float currentHealth;

		float fireRate;
		float currentFireRateCd;
	};

	void CreateSpaceship(Spaceship& spaceship);

	bool IsAccelerating();
	void SetLookingDirection(Spaceship& spaceship);
	void UpdateSpaceship(Spaceship& spaceship);
	void UpdateMovement(Spaceship& spaceship);
	void UpdatePosition(Spaceship& spaceship);
	void UpdateLookingDirection(Spaceship& spaceship);
	void CheckOutOfBonds(Spaceship& spaceship);

	void DrawSpaceship(Spaceship spaceship);
}