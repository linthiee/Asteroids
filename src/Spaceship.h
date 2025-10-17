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

		float speed;

		float maxHealth;
		float currentHealth;
	};

	void CreateSpaceship(Spaceship& spaceship);
	void UpdateSpaceship(Spaceship& spaceship);
	void DrawSpaceship(Spaceship spaceship);
}