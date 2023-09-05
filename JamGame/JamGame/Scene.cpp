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
	sellGh = LoadGraph("sell.png");

	timer = new Timer();
	timer->Initialize();

	hitBottles = new HitBottles();
	hitBottles->Init();
	// Load Sound

	//variable

	// Game Object 
}

void Scene::sceneManager() {
	titleTransaction();
	Update();
}

void Scene::Update()
{
	MousePre = Mouse;
	Mouse = GetMouseInput();
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			if (hitBottles->HitBottle(posX[i][j], posY[i][j], 60, 128))
			{
				if (((Mouse & MOUSE_INPUT_LEFT) == true) && ((MousePre & MOUSE_INPUT_LEFT) == false))
				{
					bottleHitFlag = true;
					sellPosX = posX[i][j];
					sellPosY = posY[i][j];
				}
				else
				{
					bottleHitFlag = false;
					sellPosX = -1000;
					sellPosY = -1000;
				}
			}
		}
	}
	timer->Update();
	hitBottles->Update();
}

void Scene::titleTransaction() {
	// 更新処理
	
	// 描画処理
	
	//隙間カウンター
	int crevice_count = 0;
	for (int i = 0; i < MAXPET_Y; i++)
	{
		//隙間カウンターを0に
		crevice_count = 0;
		for (int j = 0; j < MAXPET_X; j++) {
			//ペットボトルのX個を5で割った時余りが0の場合
			if (j % 5 == 0 && j != 0)
			{
				crevice_count++;
			}

			posX[i][j] = x + j * sizeX + crevice_width * crevice_count;
			posY[i][j] = y + i * sizeY + crevice_height * i;

			DrawGraph(posX[i][j], posY[i][j], petGh[i][j], TRUE);
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

void Scene::Draw()
{
	timer->Draw();
	hitBottles->Draw();
	if (bottleHitFlag)
	{
		DrawGraph(sellPosX, sellPosY, sellGh, TRUE);
	}
}

int Scene::getSceneNo() { return sceneNo; }
