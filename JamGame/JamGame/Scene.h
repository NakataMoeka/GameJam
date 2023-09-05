#pragma once
#include "DxLib.h"
#include"Timer.h"

class Scene 
{
private:
	int sceneNo;
	static const int MAXPET_X = 15;
	static const int MAXPET_Y = 4;
	const int x = 150;
	const int y = 170;
	Timer* timer;
	// Game object Instance

	//Sound
	
	//GraphHandle
	int petGh[MAXPET_Y][MAXPET_X];

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

