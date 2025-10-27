#pragma once
#include <string>
#include "raylib.h"

namespace TEXT
{
	struct Text
	{
		std::string text = "";

		float posX = 0;
		float posY = 0;

		int fonstSize = 20;
		int spacing = 0;

		Color color = WHITE;

		Font font = {};

		int fontID = 0;
	};
}
