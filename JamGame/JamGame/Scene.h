#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Key.h"
#include "Door.h"

class Scene 
{
private:
	int sceneNo;
	int isGoal;

	// Game object Instance
	Player* player;
	Key* key;
	Door* door;
	Stage* stage;

	//Sound
	int titleSound;
	int stageSound;
	
	//GraphHandle
	int titleAnimGh[21];
	int stagebackGh;
	int gameClearGh;
	int gameOverGh;
	int arrowsAnimGh[6];

	// Animation Variable
	int titleAnimTimer;
	int titleAnimCounter;

	//arrows
	char strNum2[5];

public:
	Scene(int sceneNo);
	~Scene();

	void init();
	void sceneManager();

	void titleTransaction();
	void endingTransaction();
	void gameOverTransaction();
	void playTransaction();
	void goalTransaction(Player * player, Key* key, Door* door);

	void playSound(int soundMemory);
	void drawTitle();
	void drawStage();
	void drawEnding();
	void drawGameOver();
	void drawArrows();

	int getSceneNo();

};

