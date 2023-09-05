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
	//�y�b�g�{�g���̃T�C�Y
	const int sizeX = 64;
	const int sizeY = 128;
    //���Ԃ̕�
	const int crevice_width = 30;
	const int crevice_height = 10;
	//�y�b�g�{�g����X���W
	int posX;
	//���ԃJ�E���^�[
	int crevice_count = 0;
	for (int i = 0; i < MAXPET_Y; i++)
	{
		//���ԃJ�E���^�[��0��
		crevice_count = 0;
		for (int j = 0; j < MAXPET_X; j++) {
			//�y�b�g�{�g����X��5�Ŋ��������]�肪0�̏ꍇ�A���ԃJ�E���^�[��1����
			if (j % 5 == 0 && j != 0)
			{
				crevice_count++;
			}

			posX = x + j * sizeX + crevice_width * crevice_count;

			DrawGraph(posX, y + i * sizeY + crevice_height * i, petGh[i][j], TRUE);
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
