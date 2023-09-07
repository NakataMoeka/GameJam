#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"

class Scene
{
private:
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
	//描画
	bool isDraw[MAXPET_Y][MAXPET_X];
	//消滅
	bool isDis = false;
	int randX = 0, randY = 0;
	//矢印
	int arrowSize[2] = { 64, 720 };
	int arrowPosX[2];

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

	int backgroundGh;
	int clockGh;
	int rightGh;
	int leftGh;
	// Animation Variable

	//プレイヤーがペットボトルを持っている情報
	int playerBottle[MAXPET_Y][MAXPET_X];
	bool playerHaveBottle;

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
	//getter

	int getSceneNo();

	//setter
	void SetIsChange() { isChange = !isChange; }


};

