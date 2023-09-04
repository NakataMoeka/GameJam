#include "Scene.h"
#include "math.h"

Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			petGh[i][j] = LoadGraph("pet.png");
		}
	}
	
	// Load Sound

	//variable

	// Game Object 
}

void Scene::sceneManager() {
	titleTransaction();
}

void Scene::titleTransaction() {
	// �X�V����
	
	// �`�揈��
	const int sizeX = 64;
	const int sizeY = 128;
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			DrawGraph(x + j * sizeX + 15 * j, y + i * sizeY + 10 * i, petGh[i][j], TRUE);
		}
	}
	
}


void Scene::endingTransaction() {
	//// �X�V����

	//// �`�揈��
	//playSound(endingSound);
}

void Scene::playSound(int soundMemory) {
	if (CheckSoundMem(soundMemory) == 0)
	{
		ChangeVolumeSoundMem(80, soundMemory);
		PlaySoundMem(soundMemory, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void Scene::drawTitle() {
	

	
}

int Scene::getSceneNo() { return sceneNo; }
