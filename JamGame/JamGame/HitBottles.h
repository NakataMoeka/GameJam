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
	/// �����蔻��̊֐�
	/// </summary>
	/// <param name="bottleX">������W</param>
	/// <param name="bottleY">������W</param>
	/// <param name="bottleSize">���̃T�C�Y</param>
	/// <param name="bottleSize">�c�̃T�C�Y</param>
	/// <returns>�������Ă�����true�������Ă��Ȃ�������false</returns>
	bool HitBottle(float bottleX,float bottleY, float bottleSizeX,float bottleSizeY);
};

