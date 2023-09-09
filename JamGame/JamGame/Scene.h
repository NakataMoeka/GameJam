#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"
#include"Title.h"
#include"Result.h"
class Scene
{
private:

	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

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
	static const int MAXPET_X = 12;
	static const int MAXPET_Y = 4;
	//��[�ő�
	static const int MAXREP_X = 6;
	static const int MAXREP_Y = 4;
	//�y�b�g�{�g���̃T�C�Y
	const int sizeX = 64;
	const int sizeY = 128;
	//���Ԃ̕�
	const int crevice_width = 90;
	const int crevice_height = 10;
	//���Ԃ̕�
	const int repCrevice_width = 100;
	const int repCrevice_height = 30;
	//��I�y�b�g�{�g���̍��W
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//��[�I�y�b�g�{�g���̍��W
	int repPosX[MAXPET_Y][MAXREP_X];
	int repPosY[MAXPET_Y][MAXREP_Y];
	//���ꂽ�}�[�N
	int sellPosX[MAXPET_Y][MAXPET_X];
	int sellPosY[MAXPET_Y][MAXPET_X];
	int sellSizeX = 64;
	int sellSizeY = 64;
	//��[�I�̐�
	const int MAX_REPLENISH = 7;
	int repCount[MAXPET_X][MAXREP_Y];
	//���N���b�N�����ꂽ��
	int Mouse;
	int MousePre;

	//�����ʒu
	const int x = 150;
	const int y = 170;
	const int repX = 230;
	const int repY = 120;
	//�w�i���W
	float backPos[2] = { 0,0 };
	bool isChange = false;
	//�C�[�W���O
	float position = 0;
	float etime = 0;
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
	//�����̃Q�[�W�̈ʒu
	float gaugePosX;
	float gaugePosY;
	float gaugelength;
	static const int GAUGE_SIZE_Y = 20;
	bool gaugeMoveFlag;
	//�g���b�N�̈ʒu
	float carPosX;
	float carPosY;
	static const int CAR_SIZE_X = 64;
	static const int CAR_SIZE_Y = 32;
	float carMoveLength;

	static const int WAIT_MOVE_NUM = 2;

	//�^�C�v
	enum TYPE { BUSY, USUALLY, SLOW };
	int type = USUALLY;

	int OrderType;
	int OrderNum;

	Title* title;
	Timer* timer;
	Score* score;

	Result* result;

	int sc;//�X�R�A
	int scoreCount = 0;
	int maxTime = 3;
	HitBottles* hitBottles;
	// Game object Instance

	//Sound

	//GraphHandle
	static const int MAXPETGRAHIC = 24;
	int petGh[MAXPETGRAHIC];
	int repPetGh[MAXPETGRAHIC];
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
	int carGh;
	int typeGh[3];
	// Animation Variable

	//�v���C���[���y�b�g�{�g���������Ă�����
	int playerBottle[MAXPET_Y][MAXPET_X];
	//�v���C���[�������Ă���y�b�g�{�g���̐�
	int playerHaveBottle;

	int minNum;


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
	void playTransaction();
	void endingTransaction();
	void RandomMin();//���鎞�ԃ����_��
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

