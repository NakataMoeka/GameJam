#pragma once
#include "DxLib.h"
class Timer
{
public:
	void Initialize();
	void Update();
	void Draw();
private:
	double start;
	double end;
	double dt;
	double total;
	double SetTime;

	int sec;
	int min;

	int sec1;
	int sec2;
	int min1;
	int min2;

	int timeGraph[4];
	int colonGraph;
};

