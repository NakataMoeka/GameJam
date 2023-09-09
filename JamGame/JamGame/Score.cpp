#include "Score.h"
#pragma warning(disable:4996)
void Score::Initialize()
{
	for (int i = 0; i < 8; i++)
	{
		scoreGraph[i] = LoadGraph("Resources/Num.png");
	}
	sc = 0;
}

void Score::Update()
{
	scoreNum[7] = sc % 10;
	scoreNum[6] = (sc / 10) % 10;
	scoreNum[5] = (sc / 100) % 10;
	scoreNum[4] = (sc / 1000) % 10;
	scoreNum[3] = (sc / 10000) % 10;
	scoreNum[2] = (sc / 100000) % 10;
	scoreNum[1] = (sc / 1000000) % 10;
	scoreNum[0] = (sc / 10000000) % 10;
	HighScore();
}

void Score::HighScore()
{
	FILE* fp;
	int hiscore;
	fp = fopen("score.txt", "r");
	if (fp != NULL)
	{
		fscanf(fp, "%d", &hiscore);
		fclose(fp);
	}
	if (fp == NULL || hiscore < sc)
	{
		fp = fopen("score.txt", "w");
		fprintf(fp, "%d", sc);
		fclose(fp);
	}
}

void Score::Draw()
{
	//DrawFormatString(1000, 0, GetColor(0, 0, 0), "%d", sc);
	for (int i = 0; i < 8; i++)
	{
		DrawRectExtendGraph(i * 28 + 100, 10 + 90, 28 + i * 28 + 100, 40 + 90, 110 * scoreNum[i], 0, 110, 150, scoreGraph[i], TRUE);
	}
}

int Score::GetHighetScore()
{
	FILE* fp = fopen("score.txt", "r");
	int hiscore;
	if (fp == NULL)
		return 0;
	fscanf(fp, "%d", &hiscore);
	fclose(fp);
	return hiscore;
}
