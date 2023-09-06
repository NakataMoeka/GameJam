#include "Scene.h"
#include "math.h"

Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle
	//ペットボトル
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			petGh[i][j] = LoadGraph("Resources/pet.png");
		}
	}

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			repPetGh[i][j] = LoadGraph("Resources/pet.png");
		}
	}
	sellGh = LoadGraph("sell.png");
	//背景
	backgroundGh = LoadGraph("Resources/background.png");
	//時計
	clockGh = LoadGraph("Resources/clock.png");
	//矢印
	rightGh = LoadGraph("Resources/right.png");
	leftGh = LoadGraph("Resources/left.png");

	timer = new Timer();
	timer->Initialize();

	score = new Score();
	score->Initialize();
	sc = 0;

	hitBottles = new HitBottles();
	hitBottles->Init();
	// Load Sound

	//variable

	// Game Object 
	//ペットボトル描画
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			isDraw[i][j] = true;
		}
	}
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
					isDraw[i][j] = true;
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
	score->Update();
	hitBottles->Update();
}

float Scene::Ease(float start, float end, float flame)
{
	difference = end - start;
	time = flame / maxflame;
	position = difference * time + start;
	return position;
}

void Scene::BackMove()
{
	//押されたらフラグチェンジ
	for (int i = 0; i < 2; i++)
	{
		if (hitBottles->HitBottle(arrowPosX[i], 35, 55, 650))
		{
			if (MouseInputOld != 1 && MouseInput == 1)
			{
				SetIsChange();
				backFlame = 0;
			}
		}
	}

	if (isChange)
	{
		backPos[0] = Ease(0, -1280, backFlame);
		if (backFlame >= 1.0f)
		{

			backFlame = 1.0f;
		}
		else
		{
			backFlame += 0.2f;
		}
	}
	else
	{
		backPos[0] = Ease(-1280, 0, backFlame);
		if (backFlame >= 1.0f)
		{

			backFlame = 1.0f;
		}
		else
		{
			backFlame += 0.2f;
		}

	}
}

void Scene::DisappearPet()
{
	const int maxTime = 3;
	double sum = timer->GetMaxTime() - timer->GetDt();
	//マックス時間と現在の時間の差を10で割った時余りが0だったらフラグをtrue
	if ((int)sum % maxTime == 0 && sum != 0)
	{ 
		isDis = true;
	}
	else
	{
		isDis = false;
	}

	if (isDis)
	{
		isDraw[randY][randX] = false;
		if (!isDraw[randY][randX])
		{
			isDis = false;
		}
	}
	else
	{
		randX = GetRand(MAXPET_X - 1);
		randY = GetRand(MAXPET_Y - 1);
	}
	score->SetSc(sc);
}

void Scene::titleTransaction() {
	// 更新処理
	//マウスの更新
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();
	GetMousePoint(&MousePosX, &MousePosY);
	//背景移動
	BackMove();
	//消滅処理
	DisappearPet();
	
	// 描画処理
	const int WIN_WIDHT = 1280;
	//背景
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);
	//時計
	int clockSize[2] = { 256, 90 };
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] / 2, 20, clockGh, true);
	//矢印
	arrowPosX[0] = WIN_WIDHT - arrowSize[0] + backPos[0];
	arrowPosX[1] = WIN_WIDHT + backPos[0];
	DrawGraph(arrowPosX[0], 0, rightGh, true);
	DrawGraph(arrowPosX[1], 0, leftGh, true);

	DrawFormatString(0, 100, GetColor(0, 0, 0), "dt : %f", timer->GetMaxTime() - timer->GetDt());
	DrawFormatString(0, 150, GetColor(0, 0, 0), "rand x : %d y : %d", randX, randY);

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

			posX[i][j] = x + j * sizeX + crevice_width * crevice_count;
			posY[i][j] = y + i * sizeY + crevice_height * i;

			if (isDraw[i][j])
			{
				DrawGraph(backPos[0] + posX[i][j], posY[i][j], petGh[i][j], TRUE);
			}
		}
	}

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			repPosX[i][j] = x + j * sizeX + crevice_width + WIN_WIDHT;
			repPosY[i][j] = y + i * sizeY + crevice_height * i;

			DrawGraph(backPos[0] + repPosX[i][j], repPosY[i][j], repPetGh[i][j], TRUE);
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
	score->Draw();
	hitBottles->Draw();
	if (bottleHitFlag)
	{
		DrawGraph(sellPosX, sellPosY, sellGh, TRUE);
	}
}

int Scene::getSceneNo() { return sceneNo; }
