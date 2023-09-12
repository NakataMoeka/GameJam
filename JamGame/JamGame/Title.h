#pragma once
#include<DirectXMath.h>
#include "DxLib.h"
#include"Collision.h"

class Title
{
private:
	//�O���t�B�b�N
	int titleGh;
	int hitGh[2];
	int barcodeReader;
	int code;
	int startGh;
	
	//���W
	float barcodeX = 1280 / 2 - 150;
	float barcodeY = 570;
	//�}�E�X�ϐ�
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	//���N���b�N�����ꂽ��
	int Mouse;
	int MousePre;
	//�����蔻��
	bool isHit = false;
	float barcode_sizeX = 195;
	float barcode_sizeY = 50;
	float barcodeReader_sizeX = 100;
	float barcodeReader_sizeY = 25;
public:
	void Init();
	void Update();
	void Draw();

	//getter
	bool GetIsHit() { return isHit; }
};
