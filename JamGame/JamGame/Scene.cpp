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
	// 更新処理
	
	// 描画処理
	//ペットボトルのサイズ
	const int sizeX = 64;
	const int sizeY = 128;
    //隙間の幅
	const int crevice_width = 30;
	const int crevice_height = 10;
	//ペットボトルのX座標
	int posX;
	//隙間カウンター
	int crevice_count = 0;
	for (int i = 0; i < MAXPET_Y; i++)
	{
		//隙間カウンターを0に
		crevice_count = 0;
		for (int j = 0; j < MAXPET_X; j++) {
			//ペットボトルのX個を5で割った時余りが0の場合、隙間カウンターを1足す
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
	//// 更新処理

	//// 描画処理
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
