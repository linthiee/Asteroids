#include "Draw.h"
#include "Globals.h"
#include "Utils.h"

void DRAW::DrawSprite(float id, float posX, float posY, float width, float height, Color color)
{
	Texture texture;

	texture.id = static_cast<unsigned int>(id);
	texture.width = static_cast<int>(width * (static_cast<float>(EXTERNS::screenWidth) / 100.0f));
	texture.height = static_cast<int>(height * (static_cast<float>(EXTERNS::screenHeight) / 100.0f));

	DrawTexture(texture,
		static_cast<int>((posX * EXTERNS::screenWidth / 100.0f) - ((width / 2) * EXTERNS::screenWidth / 100.0f)),
		static_cast<int>((posY * EXTERNS::screenHeight / 100.0f) - ((height / 2) * EXTERNS::screenHeight / 100.0f)),
		color);
}

void DRAW::DrawSpritePro(float id, float posX, float posY, float width, float height, Color color, float rotation)
{
    Texture texture;

    texture.id = static_cast<unsigned int>(id);
    texture.width = static_cast<int>(width * (static_cast<float>(EXTERNS::screenWidth) / 100.0f));
    texture.height = static_cast<int>(height * (static_cast<float>(EXTERNS::screenHeight) / 100.0f));

    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };

    Rectangle dest =
    {
        UTILS::PercentToPixelsX(posX),
        UTILS::PercentToPixelsY(posY),
        UTILS::PercentToPixelsX(width),
        UTILS::PercentToPixelsY(height)
    };

    Vector2 origin =
    {
        dest.width / 2.0f,
        dest.height / 2.0f
    };

    DrawTexturePro(texture, source, dest, origin, rotation, color);
}

void DRAW::DrawText(TEXT::Text text)
{
	DrawTextEx(text.font, text.text.c_str(), { (text.posX * EXTERNS::screenWidth / 100.0f) - (MeasureText(text.text.c_str(), text.fonstSize)) / 2.4f, (text.posY * EXTERNS::screenHeight / 100.0f) - (text.fonstSize / 2) }, static_cast<float>(text.fonstSize), static_cast<float>(text.spacing), text.color);
}
