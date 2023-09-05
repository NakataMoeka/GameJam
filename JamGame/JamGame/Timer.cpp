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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%02d:%02d", min, sec);

	DrawRectExtendGraph(0 * 55, 0, 55 + 0 * 55, 75, 0, 110 * min2, 110, 150, timeGraph[0], TRUE);
	DrawRectExtendGraph(1 * 55, 0, 55 + 1 * 55, 75, 110 * min1, 0, 110, 150, timeGraph[1], TRUE);
	DrawRectExtendGraph(2 * 55 + 55, 0, 55 + 2 * 55 + 55, 75, 110 * sec2, 0, 110, 150, timeGraph[2], TRUE);
	DrawRectExtendGraph(3 * 55 + 55, 0, 55 + 3 * 55 + 55, 75, 110 * sec1, 0, 110, 150, timeGraph[3], TRUE);

	DrawExtendGraph(110, 0, 165, 75, colonGraph, TRUE);
}
