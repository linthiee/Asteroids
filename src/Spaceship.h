#pragma once
#include "raylib.h"
#include "Globals.h"

namespace PLAYER
{
	struct Spaceship
	{
		Vector2 direction;
		Vector2 lookingDirection;
		Vector2 position;

		float velocity;
	};
}