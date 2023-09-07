#include "Score.h"

void Score::Initialize()
{
	sc = 0;
}

void Score::Update()
{
}

void Score::Draw()
{
	DrawFormatString(1000, 0, GetColor(0, 0, 0), "%d", sc);
}
