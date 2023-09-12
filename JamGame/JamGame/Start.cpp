#include "Start.h"
#include<time.h>
void Start::Init()
{
	countGraph = LoadGraph("Resources/Num.png");
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 3;
	dt = SetTime;
	startFlag = false;
}
void Start::Update()
{
	if (dt > 0) {
		end = clock() / CLOCKS_PER_SEC;
		total = end - start;
		dt = SetTime - total;
	}
	if (dt == 0) {
		startFlag = true;
	}
	sec = ((int)dt % 60) % 10;
}

void Start::Draw()
{
	DrawRectExtendGraph(46 + 560, 200 + 100, 46 + 46 + 560, 302 + 100, 110 * sec, 0, 110, 150, countGraph, TRUE);
}
