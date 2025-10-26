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

		float speed;

		float width;
		float height;

		float maxHealth;
		float currentHealth;
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