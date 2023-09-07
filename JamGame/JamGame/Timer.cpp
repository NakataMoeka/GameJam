#include "Timer.h"

void Timer::Initialize()
{
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 18000;
	SetTime = 3600;
	dt = start;
	for (int i = 0; i < 4; i++)
	{
		timeGraph[i] = LoadGraph("Resources/Num.png");
	}
	colonGraph = LoadGraph("Resources/colon.png");
}

void Timer::Update()
{
	start = clock() / CLOCKS_PER_SEC;
	dt = start;
	start *= 600;
	start += total;
	if (start >= 35999) {
		start = (double)time(NULL);
		start = clock() / CLOCKS_PER_SEC;
		start *= 600;
	}
	hour = (int)start / 3600;
	min = (int)start % 3600 / 60;
	hour1 = hour % 10;
	hour2 = (hour / 10) % 10;
	min1 = min % 10;
	min2 = (min / 10) % 10;
}

void Timer::Draw()
{
	DrawFormatString(500, 0, GetColor(0, 0, 0), "%d", (int)start);
	DrawRectExtendGraph(0 * 28 + 560, 50, 28 + 0 * 28 + 560, 88, 110 * hour2, 0, 110, 150, timeGraph[0], TRUE);
	DrawRectExtendGraph(1 * 28 + 560, 50, 28 + 1 * 28 + 560, 88, 110 * hour1, 0, 110, 150, timeGraph[1], TRUE);
	DrawRectExtendGraph(2 * 28 + 588, 50, 28 + 2 * 28 + 588, 88, 110 * min2, 0, 110, 150, timeGraph[2], TRUE);
	DrawRectExtendGraph(3 * 28 + 588, 50, 28 + 3 * 28 + 588, 88, 110 * min1, 0, 110, 150, timeGraph[3], TRUE);
	DrawExtendGraph(616, 50, 644, 88, colonGraph, TRUE);
}
