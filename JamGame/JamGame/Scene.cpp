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
	backgroundGh = LoadGraph("Resources/background.png");
	//���v
	clockGh = LoadGraph("Resources/clock.png");
	//���
	rightGh = LoadGraph("Resources/right.png");
	leftGh = LoadGraph("Resources/left.png");

	timer = new Timer();
	score = new Score();
	hitBottles = new HitBottles();
	hitBottles->Init();
	//�^�C�g��
	title = new Title();
	title->Init();

	// Load Sound

	//variable

	// Game Object 
	//�y�b�g�{�g���`��
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

		if (MouseInputOld != 1 && MouseInput == 1 && title->GetIsHit())
		{
			timer->Initialize();
			score->Initialize();
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
			srand((unsigned int)time(NULL));
			minNum = rand() % 6;
			playerHaveBottle = false;
			sNum = GAME;
		}
	}
	else if (sNum == GAME) {
		playTransaction();
		MousePre = Mouse;
		Mouse = GetMouseInput();

		if (CheckHitKey(KEY_INPUT_R))
		{
			playerHaveBottle = false;
		}

		for (int i = 0; i < MAXPET_Y; i++)
		{
			for (int j = 0; j < MAXPET_X; j++) {
				if (hitBottles->HitBottle(posX[i][j], posY[i][j], 60, 128) && backPos[0] == 0)
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
				if (hitBottles->HitBottle(repPosX[i][j] - 1280, repPosY[i][j], 60, 128) && backPos[0] == -1280)
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
		timer->Update();
		score->Update();
		hitBottles->Update();
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
		//���̃}�[�N�̈ʒu�����߂�
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

void Scene::playTransaction() {
	// �X�V����
	
	//�w�i�ړ�
	BackMove();
	//���ŏ���
	DisappearPet();

	// �`�揈��
	const int WIN_WIDHT = 1280;
	//�w�i
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);
	//���v
	int clockSize[2] = { 256, 90 };
	DrawGraph(WIN_WIDHT / 2 - clockSize[0] / 2, 20, clockGh, true);
	//���
	arrowPosX[0] = WIN_WIDHT - arrowSize[0] + backPos[0];
	arrowPosX[1] = WIN_WIDHT + backPos[0];
	DrawGraph(arrowPosX[0], 0, rightGh, true);
	DrawGraph(arrowPosX[1], 0, leftGh, true);

	DrawFormatString(0, 100, GetColor(0, 0, 0), "maxTime : %d", minNum);
	DrawFormatString(0, 150, GetColor(0, 0, 0), "rand x : %d y : %d", randX, randY);

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

			posX[i][j] = x + j * sizeX + crevice_width * crevice_count;
			posY[i][j] = y + i * sizeY + crevice_height * i;

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

	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			repPosX[i][j] = x + j * sizeX + crevice_width + WIN_WIDHT;
			repPosY[i][j] = y + i * sizeY + crevice_height * i;

			if (j % 2 == 0)
			{
				repPetCount++;

				if (i == 0 && j == 0)
				{
					repPetCount = 0;
				}
			}

			DrawGraph(backPos[0] + repPosX[i][j], repPosY[i][j], repPetGh[repPetCount], TRUE);
			DrawFormatString(backPos[0] + repPosX[i][j], repPosY[i][j], GetColor(0, 0, 0), "%d", repCount[i][j]);
		}
	}
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
}
