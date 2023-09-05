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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", sc);
}
