#pragma once
#include "Scene.h"


class GameSystem
{
protected:
	const char* TITLE;

	const int WIN_WIDTH; //ウィンドウ横幅
	const int WIN_HEIGHT;//ウィンドウ縦幅

	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報

	Scene* scene;
	
	
public:
	GameSystem();

	void init();
	void gameLoopPre();
	void gameLoop();
	void gameLoopPost();
	
};

