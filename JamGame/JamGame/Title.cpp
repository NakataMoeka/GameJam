#include"Title.h"

void Title::Init()
{
	titleGh = LoadGraph("Resources/title.png");
}

void Title::Draw()
{
	DrawGraph(0, 0, titleGh, true);
}
