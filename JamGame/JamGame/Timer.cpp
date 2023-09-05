#include "Timer.h"
#include<time.h>
void Timer::Initialize()
{
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 180;
	dt = SetTime;
	for (int i = 0; i < 4; i++)
	{
		timeGraph[i] = LoadGraph("Resources/Num.png");
	}
	colonGraph = LoadGraph("Resources/colon.png");
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
	sec1 = sec % 10;
	sec2 = (sec / 10) % 10;
	min1 = min % 10;
	min2 = (min / 10) % 10;
}

void Timer::Draw()
{
	DrawRectExtendGraph(0 * 28 + 560, 0, 28 + 0 * 28 + 560, 38, 0, 110 * min2, 110, 150, timeGraph[0], TRUE);
	DrawRectExtendGraph(1 * 28 + 560, 0, 28 + 1 * 28 + 560, 38, 110 * min1, 0, 110, 150, timeGraph[1], TRUE);
	DrawRectExtendGraph(2 * 28 + 588, 0, 28 + 2 * 28 + 588, 38, 110 * sec2, 0, 110, 150, timeGraph[2], TRUE);
	DrawRectExtendGraph(3 * 28 + 588, 0, 28 + 3 * 28 + 588, 38, 110 * sec1, 0, 110, 150, timeGraph[3], TRUE);
	DrawExtendGraph(616, 0, 644, 38, colonGraph, TRUE);
}
