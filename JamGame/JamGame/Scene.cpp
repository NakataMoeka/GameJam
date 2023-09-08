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

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			sellGh[i][j] = LoadGraph("Resources/sell.png");
		}
	}
	//背景
	backgroundGh = LoadGraph("Resources/background.png");
	//時計
	clockGh = LoadGraph("Resources/clock.png");
	//矢印
	rightGh = LoadGraph("Resources/right.png");
	leftGh = LoadGraph("Resources/left.png");
	//発注
	orderGh = LoadGraph("Resources/order.png");
	//発注画面
	pcGh = LoadGraph("Resources/pc.png");
	//発注画面のペットボトル
	for (int j = 0; j < MAX_PCPET_NUM; j++) {
		pcPetGh[j] = LoadGraph("Resources/pet.png");
	}
	//注文ボタン
	pickUpGh = LoadGraph("Resources/pickup.png");
	gaugeGh = LoadGraph("Resources/gauge.png");
	timer = new Timer();
	timer->Initialize();

	score = new Score();
	score->Initialize();
	sc = 0;
	scoreCount = 0;
	hitBottles = new HitBottles();
	hitBottles->Init();
	// Load Sound

	//variable

	// Game Object 
	//ペットボトル描画
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			//ペットボトル描画フラグ
			isDraw[i][j] = true;
			//プレイヤーがペットボトルを持っている情報
			playerBottle[i][j] = 0;
			//補充棚の数
			repCount[i][j] = MAX_REPLENISH;
		}
	}
	
	

	playerHaveBottle = false;
}

void Scene::sceneManager() {
	titleTransaction();
	Update();
}

void Scene::Update()
{
	MousePre = Mouse;
	Mouse = GetMouseInput();

	if (CheckHitKey(KEY_INPUT_R))
	{
		playerHaveBottle = false;
	}
	if (orderFlag == false)
	{
		for (int i = 0; i < MAXPET_Y; i++)
		{
			for (int j = 0; j < MAXPET_X; j++) {
				//商品棚の当たり判定
				if (hitBottles->HitBottle(posX[i][j] + sizeX / 2, posY[i][j] + sizeY / 2, sizeX, sizeY) && backPos[0] == 0)
				{
					if (MouseInputOld != 1 && MouseInput == 1)
					{
						if (isDraw[i][j] == false && playerBottle[i][j] == 1 && playerHaveBottle > 0)
						{
							isDraw[i][j] = true;
							playerBottle[i][j] = 0;
							playerHaveBottle--;
						}
						else
						{
							playerBottle[i][j] = 0;
						}
					}
					else
					{
					}
				}
				//陳列棚の当たり判定
				if (hitBottles->HitBottle(repPosX[i][j] + sizeX / 2 - 1280, repPosY[i][j] + sizeY / 2, sizeX - 10, sizeY - 10) && backPos[0] == -1280)
				{
					if (MouseInputOld != 1 && MouseInput == 1 && playerHaveBottle < haveBottleNum)
					{
						playerBottle[i][j] = 1;
						repCount[i][j]--;
						playerHaveBottle++;
					}
					else
					{
					}
				}
			}
		}
	}
	//発注ボタンの当たり判定
	if (hitBottles->HitBottle(orderPosX + orderSizeX / 2, orderPosY + orderSizeY / 2, 128, 64))
	{
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			orderFlag = !orderFlag;
		}
	}

	//発注時の当たり判定
	if (orderFlag == true)
	{
		for (int i = 0; i < MAX_PCPET_NUM; i++)
		{
			if (MouseInputOld != 1 && MouseInput == 1)
			{
				if (playerOrderType[i] == 1 && playerOrderNum[i] < ORDER_MAX_NUM)
				{
					if (hitBottles->HitBottle(pcPetPosX[i] + sizeX / 2, pcPetPosY[i] + sizeY / 2, sizeX - 10, sizeY - 10))
					{
						pcOrderGh[OrderNum] = pcPetGh[i];
						playerOrderNum[i]++;
						OrderNum++;
					}
				}
				if ((OrderType < ORDER_MAX_TYPE && playerOrderType[i] == 0))
				{
					if (hitBottles->HitBottle(pcPetPosX[i] + sizeX / 2, pcPetPosY[i] + sizeY / 2, sizeX - 10, sizeY - 10))
					{
						pcOrderGh[OrderNum] = pcPetGh[i];
						playerOrderType[i] = 1;
						playerOrderNum[i]++;
						OrderType++;
						OrderNum++;
					}
				}
			}
		}
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			//注文ボタンの当たり判定
			if (hitBottles->HitBottle(pickUpPosX + PICKUP_SIZE_X / 2, pickUpPosY + PICKUP_SIZE_Y / 2, PICKUP_SIZE_X, PICKUP_SIZE_Y))
			{
				for (int i = 0; i < MAX_PCPET_NUM; i++)
				{
					playerOrderNum[i] = 0;
				}
				for (int i = 0; i < ORDER_MAX_NUM * ORDER_MAX_TYPE; i++)
				{
					pcOrderGh[i] = 0;
				}
				OrderType = 0;
				OrderNum = 0;
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
	if (orderFlag == false)
	{
		for (int i = 0; i < 2; i++)
		{
			if (hitBottles->HitBottle(arrowPosX[i] + 55 / 2, 35 + 650 / 2, 55, 650))
			{
				if (MouseInputOld != 1 && MouseInput == 1)
				{
					SetIsChange();
					backFlame = 0;
				}
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
			backFlame += speed;
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
			backFlame += speed;
		}

	}
}

void Scene::DisappearPet()
{

	double sum = timer->GetMaxTime() - timer->GetDt();
	//マックス時間と現在の時間の差を10で割った時余りが0だったらフラグをtrue
	if (timer->GetStart() >= 18000 && timer->GetStart() <= 25199
		|| timer->GetStart() >= 28800 && timer->GetStart() <= 32399) {
		maxTime = 2;
	}
	else if (timer->GetStart() >= 25200 && timer->GetStart() <= 28799 || timer->GetStart() >= 32400 && timer->GetStart() <= 35999) {
		maxTime = 4;
	}
	if ((int)sum % maxTime == 0 && sum != 0)
	{
		isDis = true;
		scoreCount++;
	}
	else
	{
		isDis = false;
		scoreCount = 0;
	}
	if (scoreCount == 1) {
		sc++;
	}
	if (isDis)
	{
		isDraw[randY][randX] = false;
		//売のマークの位置を決める
		for (int i = 0; i < MAXPET_Y; i++)
		{
			for (int j = 0; j < MAXPET_X; j++) {
				if (isDraw[i][j] == false)
				{
					sellPosX[i][j] = posX[i][j];
					sellPosY[i][j] = posY[i][j];
				}
			}
		}
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
	const int WIN_HEIGHT = 720;
	//背景
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);
	//時計
	int clockSize[2] = { 256, 90 };
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] / 2, 20, clockGh, true);
	//発注ボタン
	orderPosX = WIN_WIDHT / 2 - clockSize[0] - orderSizeX;
	orderPosY = orderSizeY / 2;
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] - orderSizeX, orderSizeY /2, orderGh, true);
	//矢印
	arrowPosX[0] = WIN_WIDHT - arrowSize[0] + backPos[0];
	arrowPosX[1] = WIN_WIDHT + backPos[0];
	if (orderFlag == false)
	{
		DrawGraph(arrowPosX[0], 0, rightGh, true);
		DrawGraph(arrowPosX[1], 0, leftGh, true);
	}

	DrawFormatString(0, 100, GetColor(0, 0, 0), "maxTime : %d", maxTime);
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
			else
			{
				DrawGraph(backPos[0] + sellPosX[i][j], sellPosY[i][j] + sellSizeY / 2 , sellGh[i][j], TRUE);
			}
		}
	}

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			repPosX[i][j] = x + j * sizeX + crevice_width + WIN_WIDHT;
			repPosY[i][j] = y + i * sizeY + crevice_height * i;

			DrawGraph(backPos[0] + repPosX[i][j], repPosY[i][j], repPetGh[i][j], TRUE);
			DrawFormatString(backPos[0] + repPosX[i][j], repPosY[i][j], GetColor(0, 0, 0), "%d", repCount[i][j]);
		}
	}

	//注文画面
	if (orderFlag == true)
	{
		pcPosX = WIN_WIDHT / 2 - pcSize[0] / 2;
		pcPosY = WIN_HEIGHT / 2 - pcSize[1] / 2;
		DrawGraph(pcPosX, pcPosY, pcGh, true);

		for (int j = 0; j < MAX_PCPET_NUM; j++) {
			if (j < MAX_PCPET_NUM / 2)
			{
				pcPetPosX[j] = WIN_WIDHT / 2 - pcSize[0] / 2 + (j * sizeX) + pcEdge;
				pcPetPosY[j] = WIN_HEIGHT / 2 - pcSize[1] / 2 + pcEdge;
			}
			else
			{
				pcPetPosX[j] = WIN_WIDHT / 2 - pcSize[0] / 2 + ((j - MAX_PCPET_NUM / 2) * sizeX) + pcEdge;
				pcPetPosY[j] = WIN_HEIGHT / 2 - pcSize[1] / 2 + sizeY + pcEdge;
			}
			DrawGraph(pcPetPosX[j], pcPetPosY[j], pcPetGh[j], TRUE);
		}
		for (int i = 0; i < ORDER_MAX_NUM * ORDER_MAX_TYPE; i++)
		{
			playerOrderPetPosX[i] = WIN_WIDHT / 2 - pcSize[0] / 2 + (i * sizeX / 2) + pcEdge;
			playerOrderPetPosY[i] = WIN_HEIGHT / 2 - pcSize[1] / 2 + (sizeY * 2) + pcEdge;

			DrawGraph(playerOrderPetPosX[i], playerOrderPetPosY[i], pcOrderGh[i], TRUE);
		}
		pickUpPosX = WIN_WIDHT / 2 + pcSize[0] / 2 - PICKUP_SIZE_X - pcEdge;
		pickUpPosY = WIN_HEIGHT / 2 + pcSize[1] / 2 - PICKUP_SIZE_Y - pcEdge;

		DrawGraph(pickUpPosX, pickUpPosY, pickUpGh, TRUE);
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
}

int Scene::getSceneNo() { return sceneNo; }
