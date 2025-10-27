#pragma once
#include "raylib.h"
#include "Text.h"

namespace DRAW
{
	void DrawSprite(float id, float posX, float posY, float width, float height, Color color);
	void DrawSpritePro(float id, float posX, float posY, float width, float height, Color color, float rotation);
	void DrawText(TEXT::Text text);
}
