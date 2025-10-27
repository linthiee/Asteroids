#include "Utils.h"
#include "Globals.h"

float UTILS::PercentToPixelsX(float percentX)
{
	return (percentX / 100.0f) * EXTERNS::screenWidth;
}

float UTILS::PercentToPixelsY(float percentY)
{
	return (percentY / 100.0f) * EXTERNS::screenHeight;
}

float UTILS::PixelsToPercentX(float px)
{
	return (px / EXTERNS::screenWidth) * 100.0f;
}

float UTILS::PixelsToPercentY(float py)
{
	return (py / EXTERNS::screenHeight) * 100.0f;
}