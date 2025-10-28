#include "Bomb.h"

#include "raymath.h"

#include "Globals.h"
#include "Draw.h"
#include "Utils.h"

static float bombSpeed = 25.0f;
static float spawnCooldown = 15.0f;
static float currentSpawnTimer = spawnCooldown;

void BOMB::CreateBomb(Bomb& bomb)
{
	bomb.isActive = true;
	bomb.radius = 15.0f;

	int side = GetRandomValue(0, 3);
	Vector2 startPos = { 0.0f, 0.0f };

	switch (side)
	{
	case 0:
		startPos = { static_cast<float>(GetRandomValue(0, 100)), -5.0f };
		break;
	case 1:
		startPos = { static_cast<float>(GetRandomValue(0, 100)), 105.0f };
		break;
	case 2:
		startPos = { -5.0f, static_cast<float>(GetRandomValue(0, 100)) };
		break;
	case 3:
		startPos = { 105.0f, static_cast<float>(GetRandomValue(0, 100)) };
		break;
	}

	bomb.position = startPos;

	Vector2 targetPos = { static_cast<float>(GetRandomValue(40, 60)), static_cast<float>(GetRandomValue(40, 60)) };

	Vector2 direction = Vector2Normalize(Vector2Subtract(targetPos, startPos));

	bomb.velocity = Vector2Scale(direction, bombSpeed);
}

void BOMB::CheckOutOfBonds(Bomb& bomb)
{
	if (bomb.position.x < -10.0f || bomb.position.x > 110.0f || bomb.position.y < -10.0f || bomb.position.y > 110.0f)
	{
		bomb.isActive = false;
	}
}

void BOMB::ManageBombSpawn(Bomb& bomb)
{
	if (bomb.isActive)
	{
		return;
	}

	currentSpawnTimer -= EXTERNS::deltaT;

	if (currentSpawnTimer <= 0.0f)
	{
		currentSpawnTimer = spawnCooldown;
		CreateBomb(bomb);
	}
}

void BOMB::UpdateBomb(Bomb& bomb)
{
	if (!bomb.isActive)
	{
		return;
	}

	bomb.position = Vector2Add(bomb.position, Vector2Scale(bomb.velocity, EXTERNS::deltaT));

	CheckOutOfBonds(bomb);
}

void BOMB::DrawBomb(Bomb bomb)
{
	float blink = sinf(static_cast<float>(GetTime() * 20.0f));

	if (blink > 0.0f)
	{
		DRAW::DrawSprite(static_cast<float>(EXTERNS::bombTextureID), bomb.position.x, bomb.position.y, bomb.radius, bomb.radius, DARKBLUE);
	}
}
