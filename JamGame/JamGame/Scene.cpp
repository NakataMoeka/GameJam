#include "Scene.h"
#include "math.h"

Scene::Scene(int sceneNo) {
	this->sceneNo = sceneNo;
}

void Scene::init() {
	// Load Graph Handle
	//�y�b�g�{�g��
	for (int i = 0; i < MAXPET_Y; i++)
	{
		for (int j = 0; j < MAXPET_X; j++) {
			petGh[i][j] = LoadGraph("Resources/pet.png");
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
	timer->Initialize();
	// Load Sound

	//variable

	// Game Object 
	//�y�b�g�{�g���`��
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
	timer->Update();
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
	//�����ꂽ��t���O�`�F���W
	if (MouseInputOld != 1 && MouseInput == 1)
	{
		SetIsChange();
		backFlame = 0;
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
	//�}�b�N�X���Ԃƌ��݂̎��Ԃ̍���10�Ŋ��������]�肪0��������t���O��true
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
	}
	else
	{
		randX = GetRand(MAXPET_X - 1);
		randY = GetRand(MAXPET_Y - 1);
	}
}

void Scene::titleTransaction() {
	// �X�V����
	//�}�E�X�̍X�V
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();
	GetMousePoint(&MousePosX, &MousePosY);
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
	DrawGraph(WIN_WIDHT - arrowSize[0] + backPos[0], 0, rightGh, true);
	DrawGraph(WIN_WIDHT + backPos[0], 0, leftGh, true);

	DrawFormatString(0, 100, GetColor(0, 0, 0), "dt : %f", timer->GetMaxTime() - timer->GetDt());
	DrawFormatString(0, 150, GetColor(0, 0, 0), "rand x : %d y : %d", randX, randY);

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

			if (isDraw[i][j])
			{
				DrawGraph(backPos[0] + posX, y + i * sizeY + crevice_height * i, petGh[i][j], TRUE);
			}
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

void Scene::Draw()
{
	timer->Draw();
}

int Scene::getSceneNo() { return sceneNo; }
