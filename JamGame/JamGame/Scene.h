#pragma once
#include "DxLib.h"
#include"Timer.h"
#include"Score.h"
#include"HitBottles.h"
#include"Title.h"
#include"Result.h"
#include"Human.h"
class Scene
{
private:

	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	//補充棚から持ってこれる本数の上限
	static const int haveBottleNum = 4;
	//補充棚から持ってきたボトル
	float havePlayerBottleX[haveBottleNum];
	float havePlayerBottleY[haveBottleNum];

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
	const int repCrevice_height = 45;
	//陳列棚ペットボトルの座標
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//補充棚ペットボトルの座標
	int repPosX[MAXREP_Y][MAXREP_X];
	int repPosY[MAXREP_Y][MAXREP_X];
	//補充棚から陳列棚に持ってくる時の変数
	int repToPos;
	//売れたマーク
	int sellPosX[MAXPET_Y][MAXPET_X];
	int sellPosY[MAXPET_Y][MAXPET_X];
	int sellSizeX = 64;
	int sellSizeY = 64;
	//補充棚の数
	const int MAX_REPLENISH = 7;
	int repCount[MAXPET_Y][MAXREP_X];
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
	//発注
	float orderPosX;
	float orderPosY;
	float orderSizeX = 128;
	float orderSizeY = 64;
	bool orderFlag;
	//発注画面
	float pcPosX;
	float pcPosY;
	int pcSize[2] = { 1100,594 };
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
	//発注のゲージの位置
	float gaugePosX;
	float gaugePosY;
	float gaugelength;
	static const int GAUGE_SIZE_Y = 20;
	bool gaugeMoveFlag;
	//トラックの位置
	float carPosX;
	float carPosY;
	static const int CAR_SIZE_X = 128;
	static const int CAR_SIZE_Y = 64;
	float carMoveLength;

	//枠
	int boxPos[2] = { 830, -50 };
	static const int WAIT_MOVE_NUM = 2;

	//タイプ
	enum TYPE { BUSY, USUALLY, SLOW };
	int type = USUALLY;
	//チュートリアル
	enum TUTORIAL{START, HAVE, HAVEOK, REPLENISH, REPLENISHOK, ORDER, ORDERMENU, CHOOSE,GAGEMOVE,ORDEREND,END};
	int tutorial = START;
	//発注
	int OrderType;
	int OrderNum;
	//チュートリアル
	bool isDraw_tutorial = true;

	Title* title;
	Timer* timer;
	Score* score;
	Human* human;

	Result* result;

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
	int repGh;
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
	int boxGh;
	int havePlayerBottleGh[haveBottleNum];
	int backGh;
	static const int MAXTUTORIAL = 11;
	int tutorialGh[MAXTUTORIAL];
	int clickGh;
	int repCountGh[8];
	int out;
	// Animation Variable

	//プレイヤーがペットボトルを持っている情報
	int playerBottle[MAXREP_Y][MAXREP_X];
	//プレイヤーが持っているペットボトルの数
	int playerHaveBottle;

	int minNum;

	int se;
	int sound;
	int shose[4];
public:
	enum SceneNum { TITLE, TUTORIAL, GAME, RESULT };
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
	void Collision();
	void titleTransaction();
	void tutorialTransaction();
	void playTransaction();
	void endingTransaction();
	void RandomMin();//減る時間ランダム
	void playSound(int soundMemory);
	void drawTitle();
	void Draw();
	void playDraw();

	//getter

	int getSceneNo();
	char GetKeys(int i) { return keys[i]; }
	char GetOldKeys(int i) { return keys[i]; }
	//setter
	void SetIsChange() { isChange = !isChange; }
	SceneNum sNum = TITLE;
};

