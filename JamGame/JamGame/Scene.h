#pragma once
#include "DxLib.h"

class Scene 
{
private:
	//�}�E�X�ϐ�
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	//�V�[���ԍ�
	int sceneNo;
	//�y�b�g�{�g���ő�
	static const int MAXPET_X = 15;
	static const int MAXPET_Y = 4;
	//�����ʒu
	const int x = 120;
	const int y = 170;
	//�w�i���W
	float backPos[2] = { 0,0 };
	bool isChange = false;
	//�C�[�W���O
	float position = 0;
	float time = 0;
	const float maxflame = 1.0f;
	const float PI = 3.141592f;
	float difference = 0;
	float backFlame = 0;

	// Game object Instance

	//Sound
	
	//GraphHandle
	int petGh[MAXPET_Y][MAXPET_X];
	int backgroundGh;
	// Animation Variable

	
public:
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();

	//�C�[�W���O
	float Ease(float start, float end, float flame);

	void titleTransaction();
	void endingTransaction();

	void playSound(int soundMemory);
	void drawTitle();

	//getter
	int getSceneNo();

	//setter
	void SetIsChange() { isChange = !isChange; }


};

