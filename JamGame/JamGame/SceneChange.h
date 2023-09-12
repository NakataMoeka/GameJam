#pragma once
#include"DxLib.h"
class SceneChange
{
public:
	void Init();
	void Draw();
	int GetLight() { return light; }
	bool GetFadeIn() { return fadeIn; }
	void SetFedeIn(bool fadeIn) { this->fadeIn = fadeIn; }
	void SetFedeOut(bool fadeOut) { this->fadeOut = fadeOut; }
private:
	int light = 255;
	bool fadeIn = false;
	bool fadeOut = false;
};

