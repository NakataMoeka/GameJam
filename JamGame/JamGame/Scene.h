#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"
#include"Title.h"

class Scene
{
private:

	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	//補充棚から持ってこれる本数の上限
	const int haveBottleNum = 4;

	//マウス変数
	int MousePosX;
	int MousePosY;
	int MouseInput;
	int MouseInputOld;
	//シーン番号
	int sceneNo;
	//ペットボトル最大
	static const int MAXPET_X = 12;
	static const int MAXPET_Y = 4;
	//補充最大
	static const int MAXREP_X = 6;
	static const int MAXREP_Y = 4;
	//ペットボトルのサイズ
	const int sizeX = 64;
	const int sizeY = 128;
	//隙間の幅
	const int crevice_width = 90;
	const int crevice_height = 10;
	//隙間の幅
	const int repCrevice_width = 100;
	const int repCrevice_height = 30;
	//陳列棚ペットボトルの座標
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//補充棚ペットボトルの座標
	int repPosX[MAXPET_Y][MAXREP_X];
	int repPosY[MAXPET_Y][MAXREP_Y];
	//売れたマーク
	int sellPosX[MAXPET_Y][MAXPET_X];
	int sellPosY[MAXPET_Y][MAXPET_X];
	int sellSizeX = 64;
	int sellSizeY = 64;
	//補充棚の数
	const int MAX_REPLENISH = 7;
	int repCount[MAXPET_X][MAXREP_Y];
	//左クリック押されたか
	int Mouse;
	int MousePre;

	//初期位置
	const int x = 150;
	const int y = 170;
	const int repX = 230;
	const int repY = 120;
	//背景座標
	float backPos[2] = { 0,0 };
	bool isChange = false;
	//イージング
	float position = 0;
	float etime = 0;
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

	Title* title;
	Timer* timer;
	Score* score;
	int sc;//スコア
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
	// Animation Variable

	//プレイヤーがペットボトルを持っている情報
	int playerBottle[MAXPET_Y][MAXPET_X];
	//プレイヤーが持っているペットボトルの数
	int playerHaveBottle;

	int minNum;


public:
	enum SceneNum { TITLE, GAME, RESULT };
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
	void playTransaction();
	void endingTransaction();
	void RandomMin();//減る時間ランダム
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

