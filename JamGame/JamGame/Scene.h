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
	//ペットボトルのサイズ
	const int sizeX = 64;
	const int sizeY = 128;
	//隙間の幅
	const int crevice_width = 30;
	const int crevice_height = 10;
	//ペットボトルの座標
	int posX[MAXPET_Y][MAXPET_X];
	int posY[MAXPET_Y][MAXPET_X];
	//当たっているかの確認
	bool bottleHitFlag;
	int sellPosX;
	int sellPosY;
	//左クリック押されたか
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

