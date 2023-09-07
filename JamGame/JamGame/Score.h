#pragma once
#include"DxLib.h"
class Score
{
public:
	void Initialize();
	void Update();
	void Draw();
	void SetSc(int sc) { this->sc = sc; }
private:
	int sc;
};

