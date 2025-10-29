#pragma once
#include "raylib.h"
#include "Text.h"

namespace BUTTONS
{
	struct Button
	{
		TEXT::Text text;

		Vector2 position = {};

		float width = 5.0f;
		float height = 6.0f;

		Color color = WHITE;

		int currentTextureID = 0;

		bool isMuted = false;
	};
	void Initialize(Button& button, float width, float height, float posX, float posY);
	void Draw(Button& button);
}
