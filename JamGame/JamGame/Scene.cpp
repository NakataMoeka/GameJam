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

	timer = new Timer();
	timer->Initialize();
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
	timer->Update();
}

float Scene::Ease(float start, float end, float flame)
{
	difference = end - start;
	time = flame / maxflame;
	position = difference * time + start;
	return position;
}

void Scene::titleTransaction() {
	// �X�V����
	//�}�E�X�̍X�V
	MouseInputOld = MouseInput;
	MouseInput = GetMouseInput();
	GetMousePoint(&MousePosX, &MousePosY);
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

	
	// �`�揈��
	//�w�i
	DrawGraph(backPos[0], backPos[1], backgroundGh, true);

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

			DrawGraph(backPos[0] + posX, y + i * sizeY + crevice_height * i, petGh[i][j], TRUE);
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
