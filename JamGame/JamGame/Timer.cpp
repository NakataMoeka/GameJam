#include "Timer.h"
#include<time.h>
void Timer::Initialize()
{
	Start();
	total = 0.0;
	total2 = 0.0;
	SetTime = 600;
	tTime = 300;
	dt = tTime;
	dt2 = SetTime;
	for (int i = 0; i < 4; i++)
	{
		timeGraph[i] = LoadGraph("Resources/Num.png");
	}
	colonGraph = LoadGraph("Resources/colon.png");
}

void Timer::Update()
{
	if (dt < 600 && dt2>0) {
		end = clock() / CLOCKS_PER_SEC;
		total = end - start;
		total *= 2;
		dt = tTime + total;
		total2 = end - start;
		dt2 = SetTime - total2;
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
	//DrawFormatString(500, 0, GetColor(0, 0, 0), "%d", (int)dt);
	int size = 33;
	int y1 = 35;
	int y2 = y1 + size;
	DrawRectExtendGraph(0 * 28 + 560, y1, 28 + 0 * 28 + 560, y2, 110 * min2, 0, 110, 150, timeGraph[0], TRUE);
	DrawRectExtendGraph(1 * 28 + 560, y1, 28 + 1 * 28 + 560, y2, 110 * min1, 0, 110, 150, timeGraph[1], TRUE);
	DrawRectExtendGraph(2 * 28 + 588, y1, 28 + 2 * 28 + 588, y2, 110 * sec2, 0, 110, 150, timeGraph[2], TRUE);
	DrawRectExtendGraph(3 * 28 + 588, y1, 28 + 3 * 28 + 588, y2, 110 * sec1, 0, 110, 150, timeGraph[3], TRUE);
	DrawExtendGraph(616, y1, 644, y2, colonGraph, TRUE);
}

void Timer::Start()
{
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
}
