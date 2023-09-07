#pragma once
#include "DxLib.h"
class Timer
{
public:
	void Initialize();
	void Update();
	void Draw();

	//getter
	double GetDt() { return dt; }
	double GetDt2() { return dt2; }
	double GetMaxTime() { return SetTime; }
private:
	double start;
	double end;
	double dt;
	double dt2;
	double total;
	double total2;
	double SetTime;
	double tTime;
	int sec;
	int min;

	int sec1;
	int sec2;
	int min1;
	int min2;

	int timeGraph[4];
	int colonGraph;
};