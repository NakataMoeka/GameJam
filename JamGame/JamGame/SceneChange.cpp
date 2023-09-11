#include "SceneChange.h"

void SceneChange::Init()
{
	light = 255;
	fadeOut = true;
	fadeIn = false;
}

void SceneChange::Draw()
{
	if (fadeOut == true) {
		light = light - 5;
		SetDrawBright(light, light, light);
		if (light <= 0) {
			//light = 0;
			fadeIn = true;
			fadeOut = false;
		}
	}
	else if (fadeIn == true) {
		//light = light + 5;
		SetDrawBright(255, 255, 255);
		if (light >= 255) {
			fadeIn = false;
		}
	}
	DrawFormatString(1000, 0, GetColor(255, 0, 0), "%d", fadeIn);
}
