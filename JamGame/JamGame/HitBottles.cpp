#include "HitBottles.h"

void HitBottles::Init()
{
}

void HitBottles::Update()
{
	GetMousePoint(&mouseX, &mouseY);
}

void HitBottles::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���W�w %d�@�@���W�x %d", mouseX, mouseY);
}

bool HitBottles::HitBottle(float bottleX, float bottleY, float bottleSizeX, float bottleSizeY)
{
	if (bottleX - bottleSizeX / 2 <= mouseX && bottleX + bottleSizeX / 2 >= mouseX)
	{
		if (bottleY - bottleSizeY / 2 <= mouseY && bottleY + bottleSizeY / 2 >= mouseY)
		{
			return true;
		}
	}
	return false;
}
