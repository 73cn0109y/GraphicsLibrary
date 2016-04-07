#pragma once

struct Key
{
	bool isDown = false;
	bool isUp = true;
	bool isHeld = false;
	float keyDownFrame = -1.0;
	int ID = -1;
};