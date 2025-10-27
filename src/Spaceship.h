#pragma once
#include "raylib.h"
#include "Text.h"

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

		int lives;
		int score;

		float radius;

		float fireRate;
		float currentFireRateCd;
	};

	void CreateSpaceship(Spaceship& spaceship);

	bool IsAccelerating();
	void SetLookingDirection(Spaceship& spaceship);
	void UpdateSpaceship(Spaceship& spaceship, TEXT::Text& score);
	void UpdateMovement(Spaceship& spaceship);
	void UpdatePosition(Spaceship& spaceship);
	void UpdateLookingDirection(Spaceship& spaceship);
	void CheckOutOfBonds(Spaceship& spaceship);

	void UpdateLives(Spaceship& spaceship);
	void ResetSpaceship(Spaceship& spaceship);

	void DrawSpaceship(Spaceship spaceship);
	void DrawLives(Spaceship spaceship);
}