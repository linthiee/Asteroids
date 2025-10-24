#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Globals.h"

namespace PLAYER
{
	struct Spaceship
	{
		Vector2 direction;
		Vector2 lookingDirection;
		Vector2 position;
		Vector2 velocity;

		float speed;

		float maxHealth;
		float currentHealth;
	};

	void CreateSpaceship(Spaceship& spaceship);

	bool IsAccelerating();
	void UpdateSpaceship(Spaceship& spaceship);

	void DrawSpaceship(Spaceship spaceship);
}