#include "Timer.h"
#include<time.h>
void Timer::Initialize()
{
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 180;
	dt = SetTime;
}

void Timer::Update()
{
	if (dt > 0) {
		end = clock() / CLOCKS_PER_SEC;
		total = end - start;
		dt = SetTime - total;
	}
}

void Timer::Draw()
{
	DrawFormatString(0,0,GetColor(255,255,255),"%d",int(dt));
}
