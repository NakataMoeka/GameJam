#pragma once
#include "DxLib.h"
class HitBottles
{
	int mouseX;
	int mouseY;

public:
	void Init();
	void Update();
	void Draw();
	/// <summary>
	/// あたり判定の関数
	/// </summary>
	/// <param name="bottleX">左上座標</param>
	/// <param name="bottleY">左上座標</param>
	/// <param name="bottleSize">横のサイズ</param>
	/// <param name="bottleSize">縦のサイズ</param>
	/// <returns>当たっていたらtrue当たっていなかったらfalse</returns>
	bool HitBottle(float bottleX,float bottleY, float bottleSizeX,float bottleSizeY);
};

