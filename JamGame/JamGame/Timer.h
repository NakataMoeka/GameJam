#pragma once
#include "DxLib.h"
class Timer
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Start();//start�ϐ���p������
	//getter
	double GetDt() { return dt; }
	double GetDt2() { return dt2; }
	double GetMaxTime() { return SetTime; }
private:
	double start;//�X�^�[�g
	double end;//�G���h
	double dt;//���݂̎���(���Z)
	double dt2;//���݂̎���(���Z)
	double total;//�G���h�ƃX�^�[�g�����������
	double total2;
	double SetTime;//�I������
	double tTime;//�X�^�[�g���̎���
	int sec;
	int min;

	int sec1;
	int sec2;
	int min1;
	int min2;

	int timeGraph[4];
	int colonGraph;
};