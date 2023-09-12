#pragma once
#include "DxLib.h"
#include"Timer.h"

class Human
{
private:
	//ウィンドウサイズ
	static const int WIN_WIDTH = 1280;
	static const int WIN_HEIGHT = 720;
	//人間最大数
	static const int MAXHUMAN = 6;
	//座標
	int posX[MAXHUMAN];
	int posY[MAXHUMAN];
	int size[2] = { 256,512 };
	//スピード
	int speed[2];
	//カウント
	int count = -1;
	int old;
	//タイマー
	int max;
	int time = 0;
	//描画
	bool isComing[MAXHUMAN];
	//画像
	int humanGh[MAXHUMAN];
	
public:
	Human();
	~Human();

	void Initialize();
	void Init();
	void Update(int maxTime, Timer* timer);
	void Draw();
	void String();

	bool GetComing(int i) { return isComing[i]; }

};
