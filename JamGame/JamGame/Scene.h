#pragma once
#include "DxLib.h"

class Scene 
{
private:
	int sceneNo;

	// Game object Instance

	//Sound
	
	//GraphHandle

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

