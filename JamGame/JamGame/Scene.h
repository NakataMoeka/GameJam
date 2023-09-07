#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"

class Scene
{
private:

	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	//��[�I���玝���Ă����{���̏��
	const int haveBottleNum = 4;

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
	//�y�b�g�{�g���̃T�C�Y
	const int sizeX = 64;
	const int sizeY = 128;
	//���Ԃ̕�
	const int crevice_width = 30;
	const int crevice_height = 10;
	//��I�y�b�g�{�g���̍��W
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//��[�I�y�b�g�{�g���̍��W
	int repPosX[MAXPET_Y][MAXPET_X];
	int repPosY[MAXPET_Y][MAXPET_X];
	//���ꂽ�}�[�N
	int sellPosX[MAXPET_Y][MAXPET_X];
	int sellPosY[MAXPET_Y][MAXPET_X];
	int sellSizeX = 64;
	int sellSizeY = 64;
	//��[�I�̐�
	const int MAX_REPLENISH = 7;
	int repCount[MAXPET_Y][MAXPET_X];
	//���N���b�N�����ꂽ��
	int Mouse;
	int MousePre;

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
	float speed = 0.2f;
	//�`��
	bool isDraw[MAXPET_Y][MAXPET_X];
	//����
	bool isDis = false;
	int randX = 0, randY = 0;
	//���
	int arrowSize[2] = { 64, 720 };
	int arrowPosX[2];

	Timer* timer;
	Score* score;
	int sc;//�X�R�A
	int scoreCount = 0;
	int maxTime = 3;
	HitBottles* hitBottles;
	// Game object Instance

	//Sound

	//GraphHandle
	int petGh[MAXPET_Y][MAXPET_X];
	int repPetGh[MAXPET_Y][MAXPET_X];
	int sellGh[MAXPET_Y][MAXPET_X];

	int backgroundGh;
	int clockGh;
	int rightGh;
	int leftGh;
	// Animation Variable

	//�v���C���[���y�b�g�{�g���������Ă�����
	int playerBottle[MAXPET_Y][MAXPET_X];

	bool tFlag = false;

	int playerHaveBottle;


public:
	enum SceneNum { TITLE, GAME, RESULT };
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();
	//�w�i�ړ�
	void BackMove();
	//�y�b�g�{�g�������鏈��
	void DisappearPet();
	//�C�[�W���O
	float Ease(float start, float end, float flame);

	void Update();
	void titleTransaction();
	void endingTransaction();

	void playSound(int soundMemory);
	void drawTitle();
	void Draw();

	//getter

	int getSceneNo();
	char GetKeys(int i) { return keys[i]; }
	char GetOldKeys(int i) { return keys[i]; }
	//setter
	void SetIsChange() { isChange = !isChange; }

	SceneNum sNum = TITLE;
};

