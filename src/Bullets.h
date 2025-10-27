#pragma once
#include <vector>
#include "raylib.h"
#include "Spaceship.h"

namespace BULLETS
{
	struct Bullets
	{
		Texture texture;
		int textureID;

		Vector2 direction;
		Vector2 position;
		Vector2 velocity;

		float height;
		float width;

		float lifeSpan;
		float currentLifeSpan;

		float speed;

		float radius;

		float angle;
	};

	bool IsShooting();

	void AssignBulletsOnCreation(std::vector<Bullets>& bullets, PLAYER::Spaceship& spaceship);
	
	void CreateBullet(Bullets& bullet, PLAYER::Spaceship spaceship);
	void UpdateBullet(Bullets& bullet);
	void DrawBullet(Bullets bullet);
	
	void DeleteBullets(std::vector<Bullets>& bullets);
}

