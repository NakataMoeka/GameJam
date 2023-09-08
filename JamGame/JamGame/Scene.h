#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"

class Scene
{
private:
	//��[�I���玝���Ă����{���̏��
	const int haveBottleNum = 4;
	//PC��ʂɉf��y�b�g�{�g���̑���
	static const int MAX_PCPET_Y = 2;
	static const int MAX_PCPET_X = 12;
	static const int MAX_PCPET_NUM = 24;
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
	//����
	float orderPosX;
	float orderPosY;
	float orderSizeX = 128;
	float orderSizeY = 64;
	bool orderFlag;
	//�������
	float pcPosX;
	float pcPosY;
	int pcSize[2] = { 1000,540 };
	const int pcEdge = 50;
	//������ʂ̃{�g��
	float pcPetPosX[MAX_PCPET_NUM];
	float pcPetPosY[MAX_PCPET_NUM];
	//1��ނɑ΂���ő咍���{��
	static const int ORDER_MAX_NUM = 4;
	//�ő咍�����
	static const int ORDER_MAX_TYPE = 7;
	//���݃v���C���[���������Ă��鐔
	int playerOrderNum[MAX_PCPET_NUM];
	//���݃v���C���[���������Ă�����
	int playerOrderType[MAX_PCPET_NUM];
	//���ۂɔ�������y�b�g�{�g��
	float playerOrderPetPosX[ORDER_MAX_NUM * ORDER_MAX_TYPE];
	float playerOrderPetPosY[ORDER_MAX_NUM * ORDER_MAX_TYPE];
	//�����{�^���̈ʒu
	float pickUpPosX;
	float pickUpPosY;
	static const int PICKUP_SIZE_X = 128;
	static const int PICKUP_SIZE_Y = 64;

	int OrderType;
	int OrderNum;

	Timer* timer;
	Score* score;
	int sc;//�X�R�A
	int scoreCount = 0;
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
	int orderGh;
	int pcGh;
	int pcPetGh[MAX_PCPET_NUM];
	int pcOrderGh[ORDER_MAX_NUM * ORDER_MAX_TYPE];
	int pickUpGh;
	int gaugeGh;
	// Animation Variable

	//�v���C���[���y�b�g�{�g���������Ă�����
	int playerBottle[MAXPET_Y][MAXPET_X];
	int playerHaveBottle;

public:
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
	int maxTime = 3;
	//getter

	int getSceneNo();

	//setter
	void SetIsChange() { isChange = !isChange; }
};

