#include "Button.h"
#include "Globals.h"
#include "Draw.h"
#include "Utils.h"

void BUTTONS::Initialize(Button& button, float width, float height, float posX, float posY)
{
	button.position = { posX, posY };
	button.width = width;
	button.height = height;

	button.text.font = EXTERNS::defaultText.font;
	button.text.posX = posX;
	button.text.posY = posY;
	button.text.fonstSize = 30;

	button.currentTextureID = EXTERNS::buttonTextureID;
}

void BUTTONS::Draw(Button& button)
{
	DRAW::DrawSprite(static_cast<float>(button.currentTextureID), static_cast<float>(button.position.x) - 0.5f, static_cast<float>(button.position.y) + 3.5f, 2 * button.width, 6 * button.height, button.color);
	DRAW::DrawText(button.text);
}
