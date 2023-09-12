#pragma once
#include "DxLib.h"
class Start
{
public:
	void Init();
	void Update();
	void Draw();
	bool GetStartFlag() { return startFlag; }
private:
	int countGraph;
	int GoGraph;
	double start;//スタート
	double end;//エンド
	double dt;//現在の時間(加算)
	double total;//エンドとスタートを引いたやつ
	double SetTime;//終了時間
	bool startFlag = false;
	int sec;
};

