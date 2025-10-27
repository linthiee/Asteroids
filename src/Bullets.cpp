#include "Bullets.h"
#include "Draw.h"
#include "Globals.h" 
#include "raymath.h"
#include "Utils.h"

static Vector2 mousePercent;

bool BULLETS::IsShooting()
{
	return IsMouseButtonDown(MOUSE_LEFT_BUTTON);;
}

void BULLETS::AssignBulletsOnCreation(std::vector<Bullets>& bullets, PLAYER::Spaceship& spaceship)
{
	if (IsShooting() && spaceship.currentFireRateCd <= 0.0f)
	{
		PlaySound(EXTERNS::shootEffectSound);

		BULLETS::Bullets newBullet;

		BULLETS::CreateBullet(newBullet, spaceship);

		bullets.push_back(newBullet);

		spaceship.currentFireRateCd = spaceship.fireRate;
	}
}

void BULLETS::CreateBullet(Bullets& bullet, PLAYER::Spaceship spaceship)
{
	bullet.textureID = EXTERNS::firstFrameLaserTextureID;

	bullet.height = 80.0f;
	bullet.width = 50.0f;

	bullet.radius = 5.0f;

	mousePercent = { UTILS::PixelsToPercentX(GetMousePosition().x), UTILS::PixelsToPercentY(GetMousePosition().y) };

	bullet.direction = Vector2Subtract(mousePercent, spaceship.position);
	bullet.direction = Vector2Normalize(bullet.direction);

	float shipTipOffset = UTILS::PixelsToPercentY(spaceship.height / 2);
	bullet.position = Vector2Add(spaceship.position, Vector2Scale(bullet.direction, shipTipOffset));

	bullet.speed = 100.0f; 
	bullet.velocity = { bullet.direction.x * bullet.speed, bullet.direction.y * bullet.speed };

	bullet.lifeSpan = 1.0f;
	bullet.currentLifeSpan = bullet.lifeSpan;

	bullet.angle = atan2f(bullet.direction.y, bullet.direction.x) * RAD2DEG;
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
	float width = UTILS::PixelsToPercentX(bullet.width);
	float height = UTILS::PixelsToPercentY(bullet.height);

	if (bullet.currentLifeSpan > 0.0f)
	{
		DRAW::DrawSpritePro(static_cast<float>(bullet.textureID), bullet.position.x, bullet.position.y, width, height, WHITE, bullet.angle);
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
