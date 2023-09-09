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
	int score1;
	int score2;
	int score3;
	int score4;
	int score5;
	int score6;
	int score7;
	int score8;
};

