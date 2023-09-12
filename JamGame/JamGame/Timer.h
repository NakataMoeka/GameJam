#pragma once
#include "DxLib.h"
class Timer
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Start();//start変数専用初期化
	//getter
	double GetDt() { return dt; }
	double GetDt2() { return dt2; }
	double GetMaxTime() { return SetTime; }
private:
	double start;//スタート
	double end;//エンド
	double dt;//現在の時間(加算)
	double dt2;//現在の時間(減算)
	double total;//エンドとスタートを引いたやつ
	double total2;
	double SetTime;//終了時間
	double tTime;//スタート時の時間
	int sec;
	int min;

	int sec1;
	int sec2;
	int min1;
	int min2;

	int timeGraph[4];
	int colonGraph;
};