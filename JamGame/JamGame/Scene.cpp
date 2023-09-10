#include "Scene.h"
#include "math.h"
#include<time.h>
Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle
	//�y�b�g�{�g��
	LoadDivGraph("Resources/petBottle.png", 24, 5, 5, 64, 128, petGh);
	//��[�y�b�g�{�g��
	LoadDivGraph("Resources/petBottle.png", 24, 5, 5, 64, 128, repPetGh);

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			sellGh[i][j] = LoadGraph("Resources/sell.png");
		}
	}
	//�w�i
	backGh = LoadGraph("Resources/back.png");
	backgroundGh = LoadGraph("Resources/background.png");
	//���v
	clockGh = LoadGraph("Resources/clock.png");
	//���
	rightGh = LoadGraph("Resources/right.png");
	leftGh = LoadGraph("Resources/left.png");
	//����
	orderGh = LoadGraph("Resources/order.png");
	//�������
	pcGh = LoadGraph("Resources/pc.png");
	//������ʂ̃y�b�g�{�g��
	LoadDivGraph("Resources/petBottle.png", 24, 5, 5, 64, 128, pcPetGh);
	//�����{�^��
	pickUpGh = LoadGraph("Resources/pickup.png");
	//�Q�[�W
	gaugeGh = LoadGraph("Resources/gauge.png");
	//�g���b�N
	carGh = LoadGraph("Resources/car.png");
	//�^�C�v
	typeGh[BUSY] = LoadGraph("Resources/busy.png");
	typeGh[USUALLY] = LoadGraph("Resources/usually.png");
	typeGh[SLOW] = LoadGraph("Resources/slow.png");
	//�g
	boxGh = LoadGraph("Resources/waku.png");
	//�݌ɐ�
	repGh = LoadGraph("Resources/rep.png");
	timer = new Timer();
	score = new Score();
	hitBottles = new HitBottles();
	hitBottles->Init();
	//�^�C�g��
	title = new Title();
	result = new Result();
	title->Init();
	//�l��
	human = new Human();
	human->Initialize();

	// Load Sound
	se = LoadSoundMem("Resources/Sound/�o�[�R�[�h���[�_�[.mp3"); 
	sound = LoadSoundMem("Resources/Sound/�R���r�j���X�����f�B.mp3");
	//variable

	// Game Object 
}

void Scene::sceneManager() {

	Update();
}

void Scene::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	//�ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
	//�}�E�X�̍X�V
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();
	GetMousePoint(&MousePosX, &MousePosY);
	if (sNum == TITLE) {
		titleTransaction();
		if (CheckSoundMem(sound) == 0)
		{
			PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);
		}
		if (MouseInputOld != 1 && MouseInput == 1 && title->GetIsHit())
		{
			if (CheckSoundMem(se) == 0)
			{
				PlaySoundMem(se, DX_PLAYTYPE_NORMAL, TRUE);
			}
			StopSoundMem(sound);
			timer->Initialize();
			score->Initialize();
			human->Init();
			sc = 0;
			scoreCount = 0;
			hitBottles->Init();

			for (int i = 0; i < MAXPET_Y; i++)
			{
				for (int j = 0; j < MAXPET_X; j++) {
					//�y�b�g�{�g���`��t���O
					isDraw[i][j] = true;
					//�v���C���[���y�b�g�{�g���������Ă�����
					playerBottle[i][j] = 0;
					//��[�I�̐�
					repCount[i][j] = MAX_REPLENISH;
				}
			}
			for (int i = 0; i < haveBottleNum; i++)
			{
				havePlayerBottleGh[i] = 0;
			}
			srand((unsigned int)time(NULL));
			minNum = rand() % 6;
			playerHaveBottle = 0;
			sNum = GAME;
		}
	}
	else if (sNum == GAME) {
		playTransaction();
		MousePre = Mouse;
		Mouse = GetMouseInput();

		if (CheckHitKey(KEY_INPUT_R))
		{
			playerHaveBottle = 0;
			for (int i = 0; i < haveBottleNum; i++)
			{
				havePlayerBottleGh[i] = 0;
			}
			for (int i = 0; i < MAXREP_Y; i++)
			{
				for (int j = 0; j < MAXREP_X; j++) {
					playerBottle[i][j] = 0;
				}
			}
		}
		if (orderFlag == false)
		{
			for (int i = 0; i < MAXPET_Y; i++)
			{
				for (int j = 0; j < MAXPET_X; j++) {
					//���i�I�̓����蔻��
					if (hitBottles->HitBottle(posX[i][j] + sizeX / 2, posY[i][j] + sizeY / 2, sizeX, sizeY) && backPos[0] == 0)
					{
						if (MouseInputOld != 1 && MouseInput == 1)
						{
							if ((j == 0 || j == 1))
							{
								repToPos = 0 + (i * MAXREP_X);
							}
							else if ((j == 2 || j == 3))
							{
								repToPos = 1 + (i * MAXREP_X);
							}
							else if ((j == 4 || j == 5))
							{
								repToPos = 2 + (i * MAXREP_X);
							}
							else if ((j == 6 || j == 7))
							{
								repToPos = 3 + (i * MAXREP_X);
							}
							else if ((j == 8 || j == 9))
							{
								repToPos = 4 + (i * MAXREP_X);
							}
							else if ((j == 10 || j == 11))
							{
								repToPos = 5 + (i * MAXREP_X);
							}

							if (isDraw[i][j] == false && playerBottle[i][repToPos - (i * MAXREP_X)] > 0 && playerHaveBottle > 0)
							{
								isDraw[i][j] = true;
								playerBottle[i][repToPos - (i * MAXREP_X)]--;
								playerHaveBottle--;
								for (int t = 0; t < haveBottleNum; t++)
								{
									if (havePlayerBottleGh[t] == repPetGh[repToPos])
									{
										havePlayerBottleGh[t] = 0;
										break;
									}
								}
							}
							else
							{
								//playerBottle[i][repToPos]--;
							}
						}
						else
						{
						}
					}
				}
			}
			for (int i = 0; i < MAXREP_Y; i++)
			{
				for (int j = 0; j < MAXREP_X; j++) {
					//��I�̓����蔻��
					if (hitBottles->HitBottle(repPosX[i][j] + sizeX / 2 - 1280, repPosY[i][j] + sizeY / 2, sizeX - 10, sizeY - 10) && backPos[0] == -1280)
					{
						if (MouseInputOld != 1 && MouseInput == 1 && (playerHaveBottle < haveBottleNum))
						{
							playerBottle[i][j]++;
							repCount[i][j]--;
							//��[�I���玝���Ă����{�g��
							playerHaveBottle++;
							havePlayerBottleGh[playerHaveBottle - 1] = repPetGh[(j + (i * MAXREP_X))];
						}
						else
						{
						}
					}
				}
			}
		}
		//�����{�^���̓����蔻��
		if (hitBottles->HitBottle(orderPosX + orderSizeX / 2, orderPosY + orderSizeY / 2, 128, 64))
		{
			if (MouseInputOld != 1 && MouseInput == 1)
			{
				orderFlag = !orderFlag;
			}
		}

		//�������̓����蔻��
		if (orderFlag == true)
		{
			for (int i = 0; i < MAX_PCPET_NUM; i++)
			{
				if (MouseInputOld != 1 && MouseInput == 1 && gaugeMoveFlag == false)
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
				//�����{�^���̓����蔻��
				if (hitBottles->HitBottle(pickUpPosX + PICKUP_SIZE_X / 2, pickUpPosY + PICKUP_SIZE_Y / 2, PICKUP_SIZE_X, PICKUP_SIZE_Y) && OrderNum > 0)
				{
					if (gaugeMoveFlag == false)
					{
						gaugeMoveFlag = true;
					}
				}
			}
		}
		//������ʂ���Ȃ��Ă������蔻������悤�ɂ���
		if (Collision::CubeToCubeCollision({ gaugePosX,gaugePosY }, { pickUpPosX,pickUpPosY },
			{ gaugelength , GAUGE_SIZE_Y }, { PICKUP_SIZE_X, PICKUP_SIZE_Y }))
		{
			for (int i = 0; i < MAXREP_Y; i++)
			{
				for (int j = 0; j < MAXREP_X; j++) {
					if (repCount[i][j] + playerOrderNum[(j + (i * MAXREP_X))] <= MAX_REPLENISH)
					{
						repCount[i][j] += playerOrderNum[(j + (i * MAXREP_X))];
					}
					else if (repCount[i][j] + playerOrderNum[(j + (i * MAXREP_X))] > MAX_REPLENISH)
					{
						repCount[i][j] = MAX_REPLENISH;
					}
				}
			}
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
			gaugeMoveFlag = false;
		}

		if (timer->GetDt() >= 600) {
			result->Init();
			sNum = RESULT;
		}
		timer->Update();
		score->Update();
		hitBottles->Update();
	}
	else if (sNum == RESULT) {
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
		{
			se = LoadSoundMem("Resources/Sound/�o�[�R�[�h���[�_�[.mp3");
			sound = LoadSoundMem("Resources/Sound/�R���r�j���X�����f�B.mp3");
			title->Init();
			sNum = TITLE;
		}
		result->Update();
		result->SetHightScore(score->GetHighetScore());
		result->SetScore(sc);
	}
}

void Scene::titleTransaction()
{
	//�X�V����
	title->Update();
	//�`�揈��
	drawTitle();
}

float Scene::Ease(float start, float end, float flame)
{
	difference = end - start;
	etime = flame / maxflame;
	position = difference * etime + start;
	return position;
}

void Scene::BackMove()
{
	//�����ꂽ��t���O�`�F���W
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

	switch (playerHaveBottle)
	{
	case 1:
		speed = 0.2;
		break;
	case 2:
		speed = 0.15;
		break;
	case 3:
		speed = 0.1;
		break;
	case 4:
		speed = 0.05;
		break;
	default:
		speed = 0.25;
		break;
	}
}

void Scene::DisappearPet()
{
	double sum = timer->GetMaxTime() - timer->GetDt2();
	//�}�b�N�X���Ԃƌ��݂̎��Ԃ̍���10�Ŋ��������]�肪0��������t���O��true
	RandomMin();
	if ((int)sum % maxTime == 0 && sum != 0)
	{
		isDis = true;
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
		//���̃}�[�N�̈ʒu�����߂�
		for (int i = 0; i < MAXPET_Y; i++)
		{
			for (int j = 0; j < MAXPET_X; j++) {
				if (isDraw[i][j] == false)
				{
					sellPosX[i][j] = posX[i][j];
					sellPosY[i][j] = posY[i][j];
					isDis = false;
				}
			}
		}
		if (!isDraw[randY][randX])
		{
			isDis = false;
		}
		if (scoreCount < 10) {
			scoreCount++;
		}
	}
	else
	{
		randX = GetRand(MAXPET_X - 1);
		randY = GetRand(MAXPET_Y - 1);
	}
	score->SetSc(sc);
}

void Scene::playTransaction() {
	// �X�V����
	switch (maxTime)
	{
	case 0:
		type = USUALLY;
		break;
	case 2:
		type = BUSY;
		break;
	case 4:
		type = SLOW;
		break;
	default:
		break;
	}
	//�w�i�ړ�
	BackMove();
	//���ŏ���
	DisappearPet();
	//�l�ԏ���
	human->Update(maxTime, timer);

	// �`�揈��
	const int WIN_WIDHT = 1280;
	const int WIN_HEIGHT = 720;
	//�w�i
	DrawGraph(backPos[0], backPos[1], backGh, true);
	//�l��
	human->Draw();
	//��I&��[�I
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);
	//���v
	int clockSize[2] = { 256, 90 };
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] / 2, 20, clockGh, true);
	//�^�C�v
	int typeSize = 64;
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] / 2 - typeSize - 20, 40, typeGh[type], true);
	//�g
	DrawGraph(boxPos[0], boxPos[1], boxGh, true);
	//�����{�^��
	orderPosX = WIN_WIDHT / 2 - clockSize[0] - orderSizeX;
	orderPosY = orderSizeY / 2;
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] - orderSizeX, orderSizeY / 2, orderGh, true);
	//���
	arrowPosX[0] = WIN_WIDHT - arrowSize[0] + backPos[0] - 20;
	arrowPosX[1] = WIN_WIDHT + backPos[0] + 20;
	if (orderFlag == false)
	{
		DrawGraph(arrowPosX[0], 0, rightGh, true);
		DrawGraph(arrowPosX[1], 0, leftGh, true);
	}

	//DrawFormatString(0, 200, GetColor(0, 0, 0), "maxTime : %d", maxTime);
	//DrawFormatString(0, 150, GetColor(0, 0, 0), "rand x : %d y : %d", randX, randY);

	//���ԃJ�E���^�[
	int crevice_count = 0;
	int petCount = 0;
	int repPetCount = 0;

	for (int i = 0; i < MAXPET_Y; i++)
	{
		//���ԃJ�E���^�[��0��
		crevice_count = 0;
		for (int j = 0; j < MAXPET_X; j++) {
			//�y�b�g�{�g����X��5�Ŋ��������]�肪0�̏ꍇ�A���ԃJ�E���^�[��1����
			if (j % 4 == 0 && j != 0)
			{
				crevice_count++;
			}

			if (j % 2 == 0)
			{
				petCount++;

				if (i == 0 && j == 0)
				{
					petCount = 0;
				}
			}

			posX[i][j] = x + 150 + j * sizeX + crevice_width * crevice_count;
			posY[i][j] = y + 160 + i * sizeY + crevice_height * i;

			if (isDraw[i][j])
			{
				DrawGraph(backPos[0] + posX[i][j], posY[i][j], petGh[petCount], TRUE);
			}
			else
			{
				DrawGraph(backPos[0] + sellPosX[i][j], sellPosY[i][j] + sellSizeY / 2, sellGh[i][j], TRUE);
			}
		}
	}

	for (int i = 0; i < MAXREP_Y; i++)
	{
		for (int j = 0; j < MAXREP_X; j++) {
			repPosX[i][j] = repX + 160 + j * sizeX + repCrevice_width * j + WIN_WIDHT;
			repPosY[i][j] = repY + 130 + i * (sizeY * 0.8f) + repCrevice_height * i;

			if (i == 0 && j == 0)
			{
				repPetCount = 0;
			}
			else
			{
				repPetCount++;
			}

			DrawGraph(backPos[0] + repPosX[i][j] + sizeX, repPosY[i][j], repGh, true);
			DrawGraph(backPos[0] + repPosX[i][j], repPosY[i][j], repPetGh[repPetCount], TRUE);
			DrawFormatString(backPos[0] + repPosX[i][j] + sizeX + 40, repPosY[i][j] + (sizeY / 4 * 3), GetColor(0, 0, 0), "%d", repCount[i][j]);
		}
	}

	//�v���C���[�������Ă���{�g��
	for (int i = 0; i < haveBottleNum; i++)
	{
		DrawGraph(boxPos[0] + (i * sizeX) , boxPos[1], havePlayerBottleGh[i], TRUE);
	}

	//������ʂ���Ȃ��Ă��Q�[�W�͓�����
	if (gaugeMoveFlag == true)
	{
		gaugelength += WAIT_MOVE_NUM;
		carMoveLength += WAIT_MOVE_NUM;
	}
	else
	{
		gaugelength = 20;
		carMoveLength = 0;
	}

	//�������
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
		//�Q�[�W
		gaugePosX = WIN_WIDHT / 2 - pcSize[0] / 2 + pcEdge;
		gaugePosY = WIN_HEIGHT / 2 + pcSize[1] / 2 + GAUGE_SIZE_Y - pcEdge * 2 + 10;

		DrawExtendGraph(gaugePosX, gaugePosY, gaugePosX + gaugelength, gaugePosY + GAUGE_SIZE_Y, gaugeGh, TRUE);

		//�g���b�N
		carPosX = WIN_WIDHT / 2 - pcSize[0] / 2 + pcEdge - GAUGE_SIZE_Y;
		carPosY = WIN_HEIGHT / 2 + pcSize[1] / 2 + GAUGE_SIZE_Y - pcEdge * 2 - GAUGE_SIZE_Y;

		DrawExtendGraph(carPosX + carMoveLength, carPosY, carPosX + CAR_SIZE_X + carMoveLength, carPosY + CAR_SIZE_Y, carGh, TRUE);

		//�����{�^��
		pickUpPosX = WIN_WIDHT / 2 + pcSize[0] / 2 - PICKUP_SIZE_X - pcEdge;
		pickUpPosY = WIN_HEIGHT / 2 + pcSize[1] / 2 - PICKUP_SIZE_Y - pcEdge;

		DrawGraph(pickUpPosX, pickUpPosY, pickUpGh, TRUE);
	}

	//human->String();
}


void Scene::endingTransaction() {
	//// �X�V����

	//// �`�揈��
	//playSound(endingSound);
}

void Scene::RandomMin()
{
	if (minNum == 1) {
		if (timer->GetDt() >= 300 && timer->GetDt() <= 320
			|| timer->GetDt() >= 480 && timer->GetDt() <= 500
			|| timer->GetDt() >= 530 && timer->GetDt() <= 550) {
			maxTime = 2;
		}
		else if (timer->GetDt() >= 360 && timer->GetDt() <= 380 || timer->GetDt() >= 580 && timer->GetDt() <= 600) {
			maxTime = 4;
		}
	}
	else if (minNum == 2) {
		if (timer->GetDt() >= 320 && timer->GetDt() <= 340
			|| timer->GetDt() >= 440 && timer->GetDt() <= 460
			|| timer->GetDt() >= 560 && timer->GetDt() <= 580) {
			maxTime = 4;
		}
		else if (timer->GetDt() >= 380 && timer->GetDt() <= 400 || timer->GetDt() >= 520 && timer->GetDt() <= 540) {
			maxTime = 2;
		}
	}
	else if (minNum == 3) {
		if (timer->GetDt() >= 310 && timer->GetDt() <= 330
			|| timer->GetDt() >= 410 && timer->GetDt() <= 430
			|| timer->GetDt() >= 570 && timer->GetDt() <= 590) {
			maxTime = 2;
		}
		else if (timer->GetDt() >= 350 && timer->GetDt() <= 370 || timer->GetDt() >= 490 && timer->GetDt() <= 510) {
			maxTime = 4;
		}
	}
	else if (minNum == 4) {
		if (timer->GetDt() >= 320 && timer->GetDt() <= 340
			|| timer->GetDt() >= 420 && timer->GetDt() <= 440
			|| timer->GetDt() >= 560 && timer->GetDt() <= 580) {
			maxTime = 4;
		}
		else if (timer->GetDt() >= 380 && timer->GetDt() <= 400 || timer->GetDt() >= 520 && timer->GetDt() <= 540) {
			maxTime = 2;
		}
	}
	else if (minNum == 5) {
		if (timer->GetDt() >= 300 && timer->GetDt() <= 320
			|| timer->GetDt() >= 470 && timer->GetDt() <= 490
			|| timer->GetDt() >= 530 && timer->GetDt() <= 550) {
			maxTime = 2;
		}
		else if (timer->GetDt() >= 340 && timer->GetDt() <= 360 || timer->GetDt() >= 420 && timer->GetDt() <= 440) {
			maxTime = 4;
		}
	}
}

void Scene::playSound(int soundMemory) {
	if (CheckSoundMem(soundMemory) == 0)
	{
		ChangeVolumeSoundMem(80, soundMemory);
		PlaySoundMem(soundMemory, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void Scene::drawTitle() {

	title->Draw();
}

void Scene::Draw()
{
	if (sNum == GAME) {
		timer->Draw();
		score->Draw();
		hitBottles->Draw();
	}
	else if (sNum == RESULT) {
		result->Draw();
	}
}
