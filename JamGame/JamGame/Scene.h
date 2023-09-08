#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"

class Scene
{
private:
	//補充棚から持ってこれる本数の上限
	const int haveBottleNum = 4;
	//PC画面に映るペットボトルの総数
	static const int MAX_PCPET_Y = 2;
	static const int MAX_PCPET_X = 12;
	static const int MAX_PCPET_NUM = 24;
	//マウス変数
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	//シーン番号
	int sceneNo;
	//ペットボトル最大
	static const int MAXPET_X = 15;
	static const int MAXPET_Y = 4;
	//ペットボトルのサイズ
	const int sizeX = 64;
	const int sizeY = 128;
	//隙間の幅
	const int crevice_width = 30;
	const int crevice_height = 10;
	//陳列棚ペットボトルの座標
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//補充棚ペットボトルの座標
	int repPosX[MAXPET_Y][MAXPET_X];
	int repPosY[MAXPET_Y][MAXPET_X];
	//売れたマーク
	int sellPosX[MAXPET_Y][MAXPET_X];
	int sellPosY[MAXPET_Y][MAXPET_X];
	int sellSizeX = 64;
	int sellSizeY = 64;
	//補充棚の数
	const int MAX_REPLENISH = 7;
	int repCount[MAXPET_Y][MAXPET_X];
	//左クリック押されたか
	int Mouse;
	int MousePre;

	//初期位置
	const int x = 120;
	const int y = 170;
	//背景座標
	float backPos[2] = { 0,0 };
	bool isChange = false;
	//イージング
	float position = 0;
	float time = 0;
	const float maxflame = 1.0f;
	const float PI = 3.141592f;
	float difference = 0;
	float backFlame = 0;
	float speed = 0.2f;
	//描画
	bool isDraw[MAXPET_Y][MAXPET_X];
	//消滅
	bool isDis = false;
	int randX = 0, randY = 0;
	//矢印
	int arrowSize[2] = { 64, 720 };
	int arrowPosX[2];
	//発注
	float orderPosX;
	float orderPosY;
	float orderSizeX = 128;
	float orderSizeY = 64;
	bool orderFlag;
	//発注画面
	float pcPosX;
	float pcPosY;
	int pcSize[2] = { 1000,540 };
	const int pcEdge = 50;
	//発注画面のボトル
	float pcPetPosX[MAX_PCPET_NUM];
	float pcPetPosY[MAX_PCPET_NUM];
	//1種類に対する最大注文本数
	static const int ORDER_MAX_NUM = 4;
	//最大注文種類
	static const int ORDER_MAX_TYPE = 7;
	//現在プレイヤーが注文している数
	int playerOrderNum[MAX_PCPET_NUM];
	//現在プレイヤーが注文している種類
	int playerOrderType[MAX_PCPET_NUM];
	//実際に発注するペットボトル
	float playerOrderPetPosX[ORDER_MAX_NUM * ORDER_MAX_TYPE];
	float playerOrderPetPosY[ORDER_MAX_NUM * ORDER_MAX_TYPE];
	//注文ボタンの位置
	float pickUpPosX;
	float pickUpPosY;
	static const int PICKUP_SIZE_X = 128;
	static const int PICKUP_SIZE_Y = 64;

	int OrderType;
	int OrderNum;

	Timer* timer;
	Score* score;
	int sc;//スコア
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

	//プレイヤーがペットボトルを持っている情報
	int playerBottle[MAXPET_Y][MAXPET_X];
	int playerHaveBottle;

public:
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();
	//背景移動
	void BackMove();
	//ペットボトル消える処理
	void DisappearPet();
	//イージング
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

