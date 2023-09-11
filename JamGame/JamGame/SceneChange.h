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
private:
	int light;
	bool fadeIn;
	bool fadeOut;
};

