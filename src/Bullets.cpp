#include "Bullets.h"
#include "Draw.h"

bool BULLETS::IsShooting()
{
	return IsMouseButtonDown(MOUSE_LEFT_BUTTON);;
}

void BULLETS::AssignBulletsOnCreation(std::vector<Bullets>& bullets, PLAYER::Spaceship& spaceship)
{
	if (IsShooting() && spaceship.currentFireRateCd <= 0.0f)
	{
		BULLETS::Bullets newBullet;

		BULLETS::CreateBullet(newBullet, spaceship);

		bullets.push_back(newBullet);

		spaceship.currentFireRateCd = spaceship.fireRate;
	}
}

void BULLETS::CreateBullet(Bullets& bullet, PLAYER::Spaceship spaceship)
{
	bullet.textureID = EXTERNS::firstFrameLaserTextureID;

	bullet.height = 5.0f;
	bullet.width = 8.0f;

	Vector2 mousePos = GetMousePosition();
	bullet.direction = Vector2Subtract(mousePos, spaceship.position);

	bullet.direction = Vector2Normalize(bullet.direction);

	float shipTipOffset = spaceship.height / 2; 
	bullet.position = Vector2Add(spaceship.position, Vector2Scale(bullet.direction, shipTipOffset));

	bullet.velocity = { bullet.direction.x * bullet.speed, bullet.direction.y * bullet.speed };

	bullet.lifeSpan = 1.0f;
	bullet.currentLifeSpan = bullet.lifeSpan;
	bullet.speed = 500.0f; 

	bullet.angle = atan2f(bullet.direction.y, bullet.direction.x);
}

void BULLETS::UpdateBullet(Bullets& bullet)
{
	bullet.velocity.x = bullet.direction.x * bullet.speed;
	bullet.velocity.y = bullet.direction.y * bullet.speed;

	bullet.position.x += bullet.velocity.x * EXTERNS::deltaT;
	bullet.position.y += bullet.velocity.y * EXTERNS::deltaT;

	if (bullet.currentLifeSpan > 0.0f)
	{
		bullet.currentLifeSpan -= EXTERNS::deltaT;
	}
}

void BULLETS::DrawBullet(Bullets bullet)
{
	if (bullet.currentLifeSpan > 0.0f)
	{
		DRAW::DrawSpritePro(static_cast<float>(bullet.textureID), bullet.position.x, bullet.position.y, bullet.width, bullet.height, WHITE, bullet.angle);
		DrawCircleV(bullet.position, 5.0f, RED);
	}
}

void BULLETS::DeleteBullets(std::vector<Bullets>& bullets)
{
	for (int i = (static_cast<int>(bullets.size()) - 1); i >= 0; i--)
	{
		if (bullets[i].currentLifeSpan <= 0.0f)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}
