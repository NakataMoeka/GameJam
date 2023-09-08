#include"Title.h"

void Title::Init()
{
	titleGh = LoadGraph("Resources/title.png");
	hitGh[0] = LoadGraph("Resources/title_1.png");
	hitGh[1] = LoadGraph("Resources/title_2.png");
}

void Title::Update()
{
	//�}�E�X�̍X�V
	GetMousePoint(&MousePosX, &MousePosY);

	if (Collision::CubeToCubeCollision({ MousePosX - barcodeReader_sizeX, MousePosY - barcodeReader_sizeY },
		{ barcodeX, barcodeY }, { barcodeReader_sizeX * 2, barcodeReader_sizeY * 2 }, {barcode_sizeX * 2, barcode_sizeY * 2 }))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}
	
}

void Title::Draw()
{
	DrawGraph(0, 0, titleGh, true);

	if (isHit)
	{
		DrawGraph(0, 0, hitGh[0], true);
	}
	else
	{
		DrawGraph(0, 0, hitGh[1], true);
	}

	DrawBox(MousePosX - 100, MousePosY - 25, MousePosX + 100, MousePosY + 25, GetColor(255, 0, 0), true);
}