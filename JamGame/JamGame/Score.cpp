#include "Score.h"
#pragma warning(disable:4996)
void Score::Initialize()
{
	sc = 0;
}

void Score::Update()
{
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
	DrawFormatString(1000, 0, GetColor(0, 0, 0), "%d", sc);
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
