#pragma once
#include<DirectXMath.h>
#include "DxLib.h"
#include"Collision.h"

class Title
{
private:
	//グラフィック
	int titleGh;
	int hitGh[2];
	int barcodeReader;
	int code;
	int startGh;
	
	//座標
	float barcodeX = 1280 / 2 - 150;
	float barcodeY = 570;
	//マウス変数
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	//左クリック押されたか
	int Mouse;
	int MousePre;
	//当たり判定
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
