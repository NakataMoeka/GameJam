#pragma once
#include "DxLib.h"
#include"Timer.h"

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

	Timer* timer;
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

