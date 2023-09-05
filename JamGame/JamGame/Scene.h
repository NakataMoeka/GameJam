#pragma once
#include "DxLib.h"

class Scene 
{
private:
	int sceneNo;
	static const int MAXPET_X = 15;
	static const int MAXPET_Y = 4;
	const int x = 120;
	const int y = 170;

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

	void titleTransaction();
	void endingTransaction();

	void playSound(int soundMemory);
	void drawTitle();

	int getSceneNo();

};

