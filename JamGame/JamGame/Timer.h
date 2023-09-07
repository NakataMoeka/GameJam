#pragma once
#include "DxLib.h"
#include<time.h>
class Timer
{
public:
	void Initialize();
	void Update();
	void Draw();

	//getter
	double GetDt() { return dt; }
	double GetMaxTime() { return SetTime; }
private:
	double start;
	double dt;
	double total;
	double SetTime;

	//clock_t start, end;

	int hour;
	int min;

	int hour1;
	int hour2;
	int min1;
	int min2;

	int timeGraph[4];
	int colonGraph;
};

