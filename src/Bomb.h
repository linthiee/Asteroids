#pragma once
#include "raylib.h"

namespace BOMB
{
	struct Bomb
	{
		Vector2 position;
		Vector2 velocity;
		float radius;
		bool isActive;
	};

	void CreateBomb(Bomb& bomb);
	void CheckOutOfBonds(Bomb& bomb);

	void ManageBombSpawn(Bomb& bomb);

	void UpdateBomb(Bomb& bomb);

	void DrawBomb(Bomb bomb);
}