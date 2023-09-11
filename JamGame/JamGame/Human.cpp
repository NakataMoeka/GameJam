#include "Human.h"

Human::Human()
{
}

Human::~Human()
{
}

void Human::Initialize()
{
	//人間
	humanGh[0] = LoadGraph("Resources/human.png");
	humanGh[1] = LoadGraph("Resources/human_2.png");
	humanGh[2] = LoadGraph("Resources/human_3.png");
	humanGh[3] = LoadGraph("Resources/human_4.png");

}

void Human::Init()
{
	for (int i = 0; i < MAXHUMAN; i++)
	{
		if (i % 2 == 0)
		{
			posX[i] = WIN_WIDTH;
		}
		else
		{
			posX[i] = -size[0];
		}
		
		posY[i] = WIN_HEIGHT - size[1];
		
		//来店フラグ初期化
		isComing[i] = false;
	}

	speed[0] = 2;
	speed[1] = 4;
	count = -1;
	time = 0;

}

void Human::Update(int maxTime, Timer *timer)
{
	double sum = timer->GetMaxTime() - timer->GetDt2();
	//マックス時間と現在の時間の差を10で割った時余りが0だったらフラグをtrue
	if (time > max)
	{
		time = 0;
		count++;
		//カウント初期化
		if (count > MAXHUMAN - 1)
		{
			count = 0;
		}
		if (!isComing[count])
		{
			isComing[count] = true;
		}
	}
	else
	{
		time++;
	}

	for (int i = 0; i < MAXHUMAN; i++)
	{
		if (isComing[i])
		{
			if (i % 2 == 0)
			{
				posX[i] -= speed[0];
				if (posX[i] <= -size[0])
				{
					isComing[i] = false;
				}
			}
			else
			{
				posX[i] += speed[1];
				if (posX[i] >= WIN_WIDTH)
				{
					isComing[i] = false;
				}
			}
		}
		else
		{
			if (i % 2 == 0)
			{
				posX[i] = WIN_WIDTH;
			}
			else
			{
				posX[i] = -size[0];
			}
		}
	}

	//来店速度
	switch (maxTime)
	{
	case 3:	//普通
		max = 200;
		break;
	case 2:	//忙しい
		max = 50;
		break;
	case 4:	//暇
		max = 400;
		break;
	default:
		break;
	}
}

void Human::Draw()
{
	for (int i = 0; i < MAXHUMAN; i++)
	{
		if (i % 2 == 0)
		{
			DrawTurnGraph(posX[i], posY[i], humanGh[i], true);
		}
		else
		{
			DrawGraph(posX[i], posY[i], humanGh[i], true);
		}
		
	}

}

void Human::String()
{
	DrawFormatString(0, 0, GetColor(0, 0, 0), "count %d time %d", count, time);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "0 %s", isComing[0] ? "true" : "false");
	DrawFormatString(0, 40, GetColor(0, 0, 0), "1 %s", isComing[1] ? "true" : "false");
	DrawFormatString(0, 60, GetColor(0, 0, 0), "2 %s", isComing[2] ? "true" : "false");
	DrawFormatString(0, 80, GetColor(0, 0, 0), "3 %s", isComing[3] ? "true" : "false");
	DrawFormatString(0, 100, GetColor(0, 0, 0), "0 x %d", posX[0]);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "1 x %d", posX[1]);
}
