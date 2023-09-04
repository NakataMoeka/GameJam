#include "Scene.h"
#include "math.h"

Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle

	// Load Sound

	//variable

	// Game Object 
}

void Scene::sceneManager() {
	if (sceneNo == 0) {
		titleTransaction();
		
	}else if(sceneNo == 1) {
		
	}
	else if (sceneNo == 98) {
		endingTransaction();
	}
}

void Scene::titleTransaction() {
	// �X�V����
	
	// �`�揈��
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
