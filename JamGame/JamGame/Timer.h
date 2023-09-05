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
};

