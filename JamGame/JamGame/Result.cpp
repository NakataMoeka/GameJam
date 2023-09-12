#include "Result.h"

void Result::Init()
{
	for (int i = 0; i < 8; i++)
	{
		scoreGraph[i] = LoadGraph("Resources/Num.png");
		hightScoreGraph[i] = LoadGraph("Resources/Num.png");
	}
	PC = LoadGraph("Resources/Score.png");
	barcodeReader = LoadGraph("Resources/barcode_reader.png");
	code = LoadGraph("Resources/code.png");
	endGh = LoadGraph("Resources/end.png");
	scoreFontGh = LoadGraph("Resources/score_font.png");
}

void Result::Update()
{
	scoreNum[7] = sc % 10;
	scoreNum[6] = (sc / 10) % 10;
	scoreNum[5] = (sc / 100) % 10;
	scoreNum[4] = (sc / 1000) % 10;
	scoreNum[3] = (sc / 10000) % 10;
	scoreNum[2] = (sc / 100000) % 10;
	scoreNum[1] = (sc / 1000000) % 10;
	scoreNum[0] = (sc / 10000000) % 10;

	hightScoreNum[7] = hSc % 10;
	hightScoreNum[6] = (hSc / 10) % 10;
	hightScoreNum[5] = (hSc / 100) % 10;
	hightScoreNum[4] = (hSc / 1000) % 10;
	hightScoreNum[3] = (hSc / 10000) % 10;
	hightScoreNum[2] = (hSc / 100000) % 10;
	hightScoreNum[1] = (hSc/ 1000000) % 10;
	hightScoreNum[0] = (hSc / 10000000) % 10;

	//マウスの更新
	GetMousePoint(&MousePosX, &MousePosY);


	if (Collision::CubeToCubeCollision({ MousePosX - barcodeReader_sizeX, MousePosY - barcodeReader_sizeY },
		{ barcodeX, barcodeY }, { barcodeReader_sizeX * 2, barcodeReader_sizeY * 2 }, { barcode_sizeX * 2, barcode_sizeY * 2 }))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}
}

void Result::Draw()
{
	if (isHit)
	{
		DrawGraph(0, 0, endGh, TRUE);
	}
	else
	{
		DrawGraph(0, 0, PC, TRUE);
		DrawGraph(0, 0, scoreFontGh, true);
	}
	
	for (int i = 0; i < 8; i++)
	{
		int sY = 33;
		int y1 = 50;
		int y2 = y1 + sY;
		DrawRectExtendGraph(i * 28 + 540, y1 + 80, 28 + i * 28 + 540, y2 + 80, 110 * scoreNum[i], 0, 110, 150, scoreGraph[i], TRUE);
		DrawRectExtendGraph(i * 28 + 540, 50 + 200, 28 + i * 28 + 540, 88 + 200, 110 * hightScoreNum[i], 0, 110, 150, hightScoreGraph[i], TRUE);
	}

	DrawGraph(MousePosX - 100, MousePosY - 25, barcodeReader, true);
	DrawGraph(MousePosX - 100, MousePosY - 25 + 400, code, true);
}
