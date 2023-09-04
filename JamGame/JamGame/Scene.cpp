#include "Scene.h"
#include "math.h"

Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
	isGoal = 0;
}

void Scene::init() {
	// Load Graph Handle
	LoadDivGraph("title.png", 21, 21, 1, 1500, 800, titleAnimGh);
	LoadDivGraph("Count2.png", 6, 6, 1, 192, 32, arrowsAnimGh);
	stagebackGh = LoadGraph("background.png");
	gameClearGh = LoadGraph("gameclear.png");
	gameOverGh = LoadGraph("gameover.png");

	// Load Sound
	stageSound = LoadSoundMem("stage.mp3");

	//variable
	titleAnimTimer = 0;
	titleAnimCounter = 0;

	// Game Object 
	player = new Player(176, 650, 176, 654, 176, 654, 16, 0, 0,1);
	key = new Key(384, 425, 10, 0);
	door = new Door(576, 600, 0);
	stage = new Stage();
	stage->init();
	stage->setMap(0);
}

void Scene::sceneManager() {
	if (sceneNo == 0) {
		titleTransaction();
		if (player->getArrows() == 5) {
			player->setArrows(0);
		}
		
		if (isGoal == 1) {
			player->setStartPosX(64);
			player->setStartPosY(732);
			player->setEndPosX(64);
			player->setEndPosY(732);
			player->setPlayerPosX(64);
			player->setPlayerPosY(732);
			player->setArrows(0);
			key->setPosX(64);
			key->setPosY(80);
			key->setIsGet(0);
			door->setPosX(1370);
			door->setPosY(704);
			door->setIsScene(0);
			stage->setMap(1);
			sceneNo = 1;
			isGoal = 0;
		}
	}else if(sceneNo == 1) {
		playTransaction();
		if (player->getArrows() == 6) {
			sceneNo = 99;
		}
		if (isGoal == 1) {
			player->setStartPosX(64);
			player->setStartPosY(686);
			player->setEndPosX(64);
			player->setEndPosY(686);
			player->setPlayerPosX(64);
			player->setPlayerPosY(686);
			player->setArrows(0);
			key->setPosX(732);
			key->setPosY(128);
			key->setIsGet(0);
			door->setPosX(1242);
			door->setPosY(640);
			door->setIsScene(0);
			stage->setMap(2);
		    sceneNo = 2;
			isGoal = 0;
		}

		if (player->getMouseInput() == 2) {
			player->setStartPosX(64);
			player->setStartPosY(732);
			player->setEndPosX(64);
			player->setEndPosY(732);
			player->setPlayerPosX(64);
			player->setPlayerPosY(732);
			player->setArrows(0);
			key->setPosX(64);
			key->setPosY(80);
			key->setIsGet(0);
			door->setPosX(1370);
			door->setPosY(704);
			door->setIsScene(0);
			stage->setMap(1);
			sceneNo = 1;
			isGoal = 0;
		}
	}else if (sceneNo == 2) {
		playTransaction();
		if (player->getArrows() == 6) {
			sceneNo = 99;
		}
		if (isGoal == 1) {
			player->setStartPosX(650);
			player->setStartPosY(454);
			player->setEndPosX(650);
			player->setEndPosY(454);
			player->setPlayerPosX(650);
			player->setPlayerPosY(454);
			player->setArrows(0);
			key->setPosX(1450);
			key->setPosY(670);
			key->setIsGet(0);
			door->setPosX(30);
			door->setPosY(128);
			door->setIsScene(0);
			stage->setMap(3);
			sceneNo = 3;
			isGoal = 0;
		}

		if (player->getMouseInput() == 2) {
			player->setStartPosX(64);
			player->setStartPosY(686);
			player->setEndPosX(64);
			player->setEndPosY(686);
			player->setPlayerPosX(64);
			player->setPlayerPosY(686);
			player->setArrows(0);
			key->setPosX(732);
			key->setPosY(128);
			key->setIsGet(0);
			door->setPosX(1242);
			door->setPosY(640);
			door->setIsScene(0);
			stage->setMap(2);
			sceneNo = 2;
			isGoal = 0;
		}
	}else if (sceneNo == 3) {
		playTransaction();
		if (player->getArrows() == 6) {
			sceneNo = 99;
		}
		if (isGoal == 1) {
			player->setStartPosX(80);
			player->setStartPosY(256);
			player->setEndPosX(80);
			player->setEndPosY(256);
			player->setPlayerPosX(80);
			player->setPlayerPosY(256);
			player->setArrows(0);
			key->setPosX(1440);
			key->setPosY(134);
			key->setIsGet(0);
			door->setPosX(1400);
			door->setPosY(544);
			door->setIsScene(0);
			stage->setMap(4);
			sceneNo = 4;
			isGoal = 0;
		}

		if (player->getMouseInput() == 2) {
			player->setStartPosX(650);
			player->setStartPosY(454);
			player->setEndPosX(650);
			player->setEndPosY(454);
			player->setPlayerPosX(650);
			player->setPlayerPosY(454);
			player->setArrows(0);
			key->setPosX(1450);
			key->setPosY(670);
			key->setIsGet(0);
			door->setPosX(30);
			door->setPosY(128);
			door->setIsScene(0);
			stage->setMap(3);
			sceneNo = 3;
			isGoal = 0;
		}

		if (player->getArrows() == 6) {
			sceneNo = 99;
		}
	}else if (sceneNo == 4) {
		playTransaction();
		if (player->getMouseInput() == 2) {
			player->setStartPosX(80);
			player->setStartPosY(256);
			player->setEndPosX(80);
			player->setEndPosY(256);
			player->setPlayerPosX(80);
			player->setPlayerPosY(256);
			player->setArrows(0);
			key->setPosX(1440);
			key->setPosY(134);
			key->setIsGet(0);
			door->setPosX(1400);
			door->setPosY(544);
			door->setIsScene(0);
			stage->setMap(4);
			sceneNo = 4;
			isGoal = 0;
		}
		if (player->getArrows() == 6) {
			sceneNo = 99;
		}
		if (isGoal == 1) {
			if (isGoal == 1) {
				sceneNo = 98;
			}
		}
	}
	else if (sceneNo == 98) {
		endingTransaction();
	} else if (sceneNo == 99) {
		gameOverTransaction();
	}
}

void Scene::titleTransaction() {
	// XVˆ—
	player->update(stage, door, key);
	goalTransaction(player, key, door);
	
	// •`‰æˆ—
	playSound(stageSound);
	this->drawTitle();
	stage->draw();
	
	player->draw();
	key->draw();
	door->draw();
}


void Scene::endingTransaction() {
	//// XVˆ—

	//// •`‰æˆ—
	//playSound(endingSound);
	DrawGraph(0, 0, gameClearGh, true);
}

void Scene::gameOverTransaction() {
	//// XVˆ—
	
	
	//// •`‰æˆ—
	//playSound(gameOverSound);
	DrawGraph(0, 0, gameOverGh, true);
}

void Scene::playTransaction() {
	//// XVˆ—
	player->update(stage, door, key);
	player->isAlive();
	if (player->getisAlive() == 0) {
		sceneNo = 99;
	}
	
	goalTransaction(player, key, door);

	//// •`‰æˆ—
	playSound(stageSound);
	this->drawStage();
	stage->draw();
	door->draw();
	this->drawArrows();
	player->draw();
	key->draw();
}

void Scene::playSound(int soundMemory) {
	if (CheckSoundMem(soundMemory) == 0)
	{
		ChangeVolumeSoundMem(80, soundMemory);
		PlaySoundMem(soundMemory, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void Scene::goalTransaction(Player* player, Key* key, Door* door) {
	float p2dX = door->getPosX() - player->getPlayerPosX();
	float p2dY = door->getPosY() - player->getPlayerPosY();
	float p2d = sqrtf(pow(p2dX, 2)+ pow(p2dY,2));

	if (key->getIsGet() == 1) {
		if (p2d <= player->getRadius() + 64) {
			isGoal = 1;
			sceneNo++;
		}
	}
}

void Scene::drawTitle() {
	titleAnimTimer++;

	if (titleAnimTimer == 6) {
		titleAnimCounter++;
		if (titleAnimCounter == 21)
		{
			titleAnimCounter = 0;
		}
		titleAnimTimer = 0;
	}

	DrawGraph(0, 0, titleAnimGh[titleAnimCounter], true);
}

void Scene::drawStage() {
	DrawGraph(0, 0, stagebackGh, true);
}

void Scene::drawArrows() {
	sprintf_s(strNum2, sizeof(strNum2), "%d", player->getArrows());

		for (int t = 0; t < 6; t++)
		{
			DrawGraph(0, 768, arrowsAnimGh[strNum2[t] - '0'], TRUE);
		}
}

int Scene::getSceneNo() { return sceneNo; }
