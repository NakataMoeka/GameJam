#pragma once
#include "DxLib.h"
class Result
{
public:
	void Init();
	void Update();
	void Draw();
	void SetScore(int sc) { this->sc = sc; }
	void SetHightScore(int hSc) { this->hSc = hSc; }
private:
	int scoreGraph[8];
	int scoreNum[8];
	int hightScoreGraph[8];
	int hightScoreNum[8];
	int sc;
	int hSc;
};

