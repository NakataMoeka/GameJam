#pragma once
#include "DxLib.h"
#include"Collision.h"
class Result
{
public:
	void Init();
	void Update();
	void Draw();
	void SetScore(int sc) { this->sc = sc; }
	void SetHightScore(int hSc) { this->hSc = hSc; }
	//getter
	bool GetIsHit() { return isHit; }
private:
	int scoreGraph[8];
	int scoreNum[8];
	int hightScoreGraph[8];
	int hightScoreNum[8];
	int PC;
	int sc;
	int hSc;
	int barcodeReader;
	int code;
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
};

