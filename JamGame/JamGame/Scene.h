#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"HitBottles.h"

class Scene 
{
private:
	int sceneNo;
	static const int MAXPET_X = 15;
	static const int MAXPET_Y = 4;
	//�y�b�g�{�g���̃T�C�Y
	const int sizeX = 64;
	const int sizeY = 128;
	//���Ԃ̕�
	const int crevice_width = 30;
	const int crevice_height = 10;
	//�y�b�g�{�g���̍��W
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//�������Ă��邩�̊m�F
	bool bottleHitFlag;
	int sellPosX;
	int sellPosY;
	//���N���b�N�����ꂽ��
	int Mouse;
	int MousePre;

	const int x = 150;
	const int y = 170;
	Timer* timer;
	HitBottles *hitBottles;
	// Game object Instance

	//Sound
	
	//GraphHandle
	int petGh[MAXPET_Y][MAXPET_X];
	int sellGh;

	// Animation Variable

	
public:
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();
	void Update();
	void titleTransaction();
	void endingTransaction();

	void playSound(int soundMemory);
	void drawTitle();
	void Draw();
	int getSceneNo();

};

