#pragma once
#include"DxLib.h"
#include <stdio.h>
class Score
{
public:
	void Initialize();
	void Update();
	void HighScore();
	void Draw();
	void SetSc(int sc) { this->sc = sc; }
	int GetHighetScore();
	
private:
	int sc;
	int scoreGraph[8];
	int scoreNum[8];
};

