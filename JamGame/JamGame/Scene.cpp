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
	//�`���[�g���A���摜
	clickGh = LoadGraph("Resources/tutorial/Click.png");
	tutorialGh[START] = LoadGraph("Resources/tutorial/start.png");
	tutorialGh[HAVE] = LoadGraph("Resources/tutorial/have.png");
	tutorialGh[HAVEOK] = LoadGraph("Resources/tutorial/have_ok.png");
	tutorialGh[REPLENISH] = LoadGraph("Resources/tutorial/replenish.png");
	tutorialGh[REPLENISHOK] = LoadGraph("Resources/tutorial/replenish_ok.png");
	tutorialGh[ORDER] = LoadGraph("Resources/tutorial/order.png");
	tutorialGh[ORDERMENU] = LoadGraph("Resources/tutorial/ordermenu.png");
	tutorialGh[CHOOSE] = LoadGraph("Resources/tutorial/choose.png");
	tutorialGh[GAGEMOVE] = LoadGraph("Resources/tutorial/gamemove.png");
	tutorialGh[ORDEREND] = LoadGraph("Resources/tutorial/orderend.png");
	tutorialGh[END] = LoadGraph("Resources/tutorial/end.png");
	//�݌ɐ�
	LoadDivGraph("Resources/Num.png", 8, 8, 1, 110, 150, repCountGh);
	//�ދΎ���
	out = LoadGraph("Resources/clocking_out.png");
	//�d���J�n
	start_workGh = LoadGraph("Resources/start_work.png");

	timer = new Timer();
	score = new Score();
	hitBottles = new HitBottles();

	//�^�C�g��
	title = new Title();
	result = new Result();
	sceneChange = new SceneChange();
	start = new Start();
	title->Init();
	//�l��
	human = new Human();
	human->Initialize();
	hitBottles->Init();
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

			for (int i = 0; i < 3; i++) {
				shose[i] = LoadSoundMem("Resources/Sound/�v�C�ŕ���.mp3");
			}
			shose[3] = LoadSoundMem("Resources/Sound/�n�C�q�[���ŕ���.mp3");
			scTTFlag = true;
		}
		if (scTTFlag == true) {
			sceneChange->SetFedeOut(true);
			if (sceneChange->GetFadeIn() == true) {
				start->Init();
				sNum = TUTORIAL;
				tutorial = START;
				scRFlag = false;
				//sNum = GAME;
			}
		}
	}
	else if (sNum == TUTORIAL)
	{
		tutorialTransaction();
		Collision();
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
		{
			sNum = GAME;
			tutorial = START;
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

			for (int i = 0; i < 3; i++) {
				shose[i] = LoadSoundMem("Resources/Sound/�v�C�ŕ���.mp3");
			}
			shose[3] = LoadSoundMem("Resources/Sound/�n�C�q�[���ŕ���.mp3");
			BGM = LoadSoundMem("Resources/Sound/Cat_life.mp3");
		}
	}
	else if (sNum == GAME) {

		playTransaction();
		Collision();

		if (timer->GetDt() >= 600) {
			scGFlag = true;
		}
		if (scGFlag == true) {
			sceneChange->SetFedeOut(true);
			if (sceneChange->GetFadeIn() == true) {
				scTTFlag = false;
				result->Init();
				sNum = RESULT;
			}
		}
	}
	else if (sNum == RESULT) {

		if (MouseInputOld != 1 && MouseInput == 1 && title->GetIsHit())
		{
			se = LoadSoundMem("Resources/Sound/�o�[�R�[�h���[�_�[.mp3");
			sound = LoadSoundMem("Resources/Sound/�R���r�j���X�����f�B.mp3");
			scRFlag = true;
		}
		if (scRFlag == true) {
			sceneChange->SetFedeOut(true);
			if (sceneChange->GetFadeIn() == true) {
				title->Init();
				scGFlag = false;
				sNum = TITLE;
			}
		}
		result->Update();
		result->SetHightScore(score->GetHighetScore());
		result->SetScore(sc);
	}
}
void Scene::Collision()
{
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
							sc++;
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
						if (repCount[i][j] != 0)
						{
							playerBottle[i][j]++;
							repCount[i][j]--;
							//��[�I���玝���Ă����{�g��
							playerHaveBottle++;
						}
						havePlayerBottleGh[playerHaveBottle - 1] = repPetGh[(j + (i * MAXREP_X))];
					}
					else
					{
					}

					if (repCount[i][j] <= 0)
					{
						repCount[i][j] = 0;
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

	hitBottles->Update();
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

void Scene::titleTransaction()
{
	//�X�V����
	title->Update();
	//�`�揈��
	drawTitle();
}

void Scene::tutorialTransaction()
{
	// �X�V����
	switch (tutorial)
	{
	case START:
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			tutorial = HAVE;
		}
		break;
	case HAVE:
		isDraw[0][0] = false;

		if (playerBottle[0][0] != 0)
		{
			tutorial = HAVEOK;
		}
		break;
	case HAVEOK:
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			tutorial = REPLENISH;
		}
		break;
	case REPLENISH:
		if (isDraw[0][0])
		{
			tutorial = REPLENISHOK;
		}
		break;
	case REPLENISHOK:
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			tutorial = ORDER;
		}
		break;
	case ORDER:
		//�����{�^�����������玟��case��
		if (orderFlag)
		{
			tutorial = ORDERMENU;
		}
		break;
	case ORDERMENU:
		//�t�@���^�Ԃǂ��H��I�񂾂玟��case��
		for (int i = 0; i < ORDER_MAX_NUM * ORDER_MAX_TYPE; i++)
		{
			if (pcOrderGh[i] == pcPetGh[0])
			{
				tutorial = CHOOSE;
			}
		}
		break;
	case CHOOSE:
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			isDraw_tutorial = false;
		}
		//�����{�^�����������玟��case��
		if (gaugeMoveFlag)
		{
			tutorial = GAGEMOVE;
		}
		break;
	case GAGEMOVE:
		//������ʂŃQ�[�W�������{�^���ɐG�ꂽ�甭������
		if (orderFlag && !gaugeMoveFlag)
		{
			isDraw_tutorial = true;
			if (MouseInputOld != 1 && MouseInput == 1)
			{
				tutorial = ORDEREND;
			}
		}
		break;
	case ORDEREND:
		//��[�I�̂Ƃ���ɍs�����Đ����m�F��������I��
		if (!orderFlag && backPos[0] == -1280)
		{
			tutorial = END;
		}
		break;
	case END:
		if (MouseInputOld != 1 && MouseInput == 1)
		{
			start->Init();
			timer->Initialize();
			sNum = GAME;
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

			for (int i = 0; i < 3; i++) {
				shose[i] = LoadSoundMem("Resources/Sound/�v�C�ŕ���.mp3");
			}
			shose[3] = LoadSoundMem("Resources/Sound/�n�C�q�[���ŕ���.mp3");
			BGM = LoadSoundMem("Resources/Sound/Cat_life.mp3");
		}
		break;
	default:
		break;
	}
	//�w�i�ړ�
	BackMove();
	//���摜�ʒu
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

	// �`�揈��
	playDraw();

	if (isDraw_tutorial)
	{
		DrawGraph(0, 0, tutorialGh[tutorial], true);
		//�N���b�N
		if (tutorial == START || tutorial == HAVEOK || tutorial == REPLENISHOK || tutorial == CHOOSE || tutorial == GAGEMOVE || tutorial == END)
		{
			DrawGraph(0, 0, clickGh, true);
		}
	}
}

void Scene::playTransaction() {
	// �X�V����

		if (CheckSoundMem(BGM) == 0)
		{
			PlaySoundMem(BGM, DX_PLAYTYPE_BACK, TRUE);
			ChangeVolumeSoundMem(110, BGM);
		}
		switch (maxTime)
		{
		case 3:
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
		for (int i = 0; i < 4; i++) {
			if (human->GetComing(i)) {
				if (CheckSoundMem(shose[i]) == 0)
				{
					PlaySoundMem(shose[i], DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}
		score->Update();
		if (start->GetStartFlag() == true) {
			timer->Update();
	}
	else {
		start->Update();
	}
	// �`�揈��
	playDraw();
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

	title->Draw();
}

void Scene::Draw()
{
	if (sNum == GAME) {
		timer->Draw();
		score->Draw();
		hitBottles->Draw();
		if (start->GetStartFlag() == false) {
			start->Draw();
		}
	}
	else if (sNum == RESULT) {
		result->Draw();
	}
	sceneChange->Draw();
}

void Scene::playDraw()
{
	const int WIN_WIDHT = 1280;
	const int WIN_HEIGHT = 720;
	//�w�i
	DrawGraph(backPos[0], backPos[1], backGh, true);
	//�l��
	human->Draw();
	//��I&��[�I
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);
	//���v
	int clockSize[2] = { 240, 86 };
	DrawExtendGraph(WIN_WIDHT / 2 - clockSize[0] / 2, 10, WIN_WIDHT / 2 - clockSize[0] / 2 + clockSize[0], 10 + clockSize[1], clockGh, true);
	//�ދΎ���
	DrawGraph(backPos[0], 0, out, true);
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
			DrawExtendGraph(backPos[0] + repPosX[i][j] + sizeX - 10 + 40, repPosY[i][j] + (sizeY / 4 * 3) - 13, backPos[0] + repPosX[i][j] + sizeX - 10 + 40 + 20, repPosY[i][j] + (sizeY / 4 * 3) - 13 + 27, repCountGh[repCount[i][j]], true);
			//DrawFormatString(backPos[0] + repPosX[i][j] + sizeX + 40, repPosY[i][j] + (sizeY / 4 * 3), GetColor(0, 0, 0), "%d", repCount[i][j]);
		}
	}

	//�v���C���[�������Ă���{�g��
	for (int i = 0; i < haveBottleNum; i++)
	{
		int sX = 32;
		int sY = 64;
		DrawExtendGraph(boxPos[0] + (i * sizeX) + 20, boxPos[1] + 60, boxPos[0] + (i * sizeX) + sX + 20, boxPos[1] + sY + 60, havePlayerBottleGh[i], TRUE);
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
		DrawExtendGraph(pcPosX, pcPosY, pcPosX + pcSize[0], pcPosY + pcSize[1], pcGh, true);

		for (int j = 0; j < MAX_PCPET_NUM; j++) {
			if (j < MAX_PCPET_NUM / 2)
			{
				pcPetPosX[j] = WIN_WIDHT / 2 - pcSize[0] / 2 + (j * sizeX) + pcEdge + 120;
				pcPetPosY[j] = WIN_HEIGHT / 2 - pcSize[1] / 2 + pcEdge + 20;
			}
			else
			{
				pcPetPosX[j] = WIN_WIDHT / 2 - pcSize[0] / 2 + ((j - MAX_PCPET_NUM / 2) * sizeX) + pcEdge + 120;
				pcPetPosY[j] = WIN_HEIGHT / 2 - pcSize[1] / 2 + sizeY + pcEdge + 20;
			}
			DrawGraph(pcPetPosX[j], pcPetPosY[j], pcPetGh[j], TRUE);
		}
		for (int i = 0; i < ORDER_MAX_NUM * ORDER_MAX_TYPE; i++)
		{
			playerOrderPetPosX[i] = WIN_WIDHT / 2 - pcSize[0] / 2 + (i * sizeX / 2) + pcEdge + 40;
			playerOrderPetPosY[i] = WIN_HEIGHT / 2 - pcSize[1] / 2 + (sizeY * 2) + pcEdge + 20;

			DrawGraph(playerOrderPetPosX[i], playerOrderPetPosY[i], pcOrderGh[i], TRUE);
		}
		//�Q�[�W
		gaugePosX = WIN_WIDHT / 2 - pcSize[0] / 2 + pcEdge + 20;
		gaugePosY = WIN_HEIGHT / 2 + pcSize[1] / 2 + GAUGE_SIZE_Y - pcEdge * 2 - CAR_SIZE_Y / 2 + 15;

		DrawExtendGraph(gaugePosX, gaugePosY, gaugePosX + gaugelength, gaugePosY + GAUGE_SIZE_Y, gaugeGh, TRUE);

		//�g���b�N
		carPosX = WIN_WIDHT / 2 - pcSize[0] / 2 + pcEdge - GAUGE_SIZE_Y + 30;
		carPosY = WIN_HEIGHT / 2 + pcSize[1] / 2 + GAUGE_SIZE_Y - pcEdge * 2 - CAR_SIZE_Y / 2 - GAUGE_SIZE_Y;

		DrawExtendGraph(carPosX + carMoveLength, carPosY, carPosX + CAR_SIZE_X + carMoveLength, carPosY + CAR_SIZE_Y, carGh, TRUE);

		//�����{�^��
		pickUpPosX = WIN_WIDHT / 2 + pcSize[0] / 2 - PICKUP_SIZE_X - pcEdge - 25;
		pickUpPosY = WIN_HEIGHT / 2 + pcSize[1] / 2 - PICKUP_SIZE_Y - pcEdge - 25;

		DrawGraph(pickUpPosX, pickUpPosY, pickUpGh, TRUE);
	}

	//human->String();
}

float Scene::Ease(float start, float end, float flame)
{
	difference = end - start;
	etime = flame / maxflame;
	position = difference * etime + start;
	return position;
}