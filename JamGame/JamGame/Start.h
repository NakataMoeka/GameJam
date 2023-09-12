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
	double start;//�X�^�[�g
	double end;//�G���h
	double dt;//���݂̎���(���Z)
	double total;//�G���h�ƃX�^�[�g�����������
	double SetTime;//�I������
	bool startFlag = false;
	int sec;
};

