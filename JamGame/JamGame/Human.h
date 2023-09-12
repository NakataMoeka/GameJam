#pragma once
#include "DxLib.h"
#include"Timer.h"

class Human
{
private:
	//�E�B���h�E�T�C�Y
	static const int WIN_WIDTH = 1280;
	static const int WIN_HEIGHT = 720;
	//�l�ԍő吔
	static const int MAXHUMAN = 6;
	//���W
	int posX[MAXHUMAN];
	int posY[MAXHUMAN];
	int size[2] = { 256,512 };
	//�X�s�[�h
	int speed[2];
	//�J�E���g
	int count = -1;
	int old;
	//�^�C�}�[
	int max;
	int time = 0;
	//�`��
	bool isComing[MAXHUMAN];
	//�摜
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
