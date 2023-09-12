#include "Start.h"
#include<time.h>
void Start::Init()
{

	GoGraph = LoadGraph("Resources/start_work.png");
	start = (double)time(NULL);
	start = clock() / CLOCKS_PER_SEC;
	total = 0.0;
	SetTime = 5;
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
	DrawGraph(0, 0, GoGraph, TRUE);
}
