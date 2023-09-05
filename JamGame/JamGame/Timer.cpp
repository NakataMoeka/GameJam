#include "Timer.h"
#include<time.h>
void Timer::Initialize()
{
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 140;
	dt = SetTime;
}

void Timer::Update()
{
	if (dt > 0) {
		end = clock() / CLOCKS_PER_SEC;
		total = end - start;
		dt = SetTime - total;
	}
	min = (int)dt % 3600 / 60;
	sec = (int)dt % 60;
}

void Timer::Draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%02d:%02d", min, sec);
}
