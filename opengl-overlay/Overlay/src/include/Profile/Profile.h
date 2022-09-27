#pragma once
#include <string>

struct Profile
{
	int style = 0;
	float color[3] = { 255, 255, 255 };
	float scale = 1.f;
	float thickness = 1.f;
	float gap = 0;
	int xOffset = 0;
	int yOffset = 0;
};
