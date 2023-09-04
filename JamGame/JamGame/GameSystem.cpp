#include "DxLib.h"
#include "GameSystem.h"


GameSystem::GameSystem() : WIN_WIDTH(1500), WIN_HEIGHT(800) {
	ChangeWindowMode(TRUE); //ウィンドウモードに設定

	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	
	SetMainWindowText("5 ARROWS"); // タイトルを変更
	
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32); //画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）

	SetWindowSizeExtendRate(1.0); //画面サイズを設定（解像度との比率で設定）
	
	SetBackgroundColor(0x00, 0x00, 0x00); // 画面の背景色を設定する

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);
}

void GameSystem::init() {
	scene = new Scene(0);
	scene->init();
}

void GameSystem::gameLoopPre() {
	//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存

	//最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	//画面クリア
	ClearDrawScreen();
	//---------  ここからプログラムを記述  ----------//
}

void GameSystem::gameLoop() {
	scene->sceneManager();
}

void GameSystem::gameLoopPost() {

	//---------  ここまでにプログラムを記述  ---------//
	ScreenFlip();//（ダブルバッファ）裏面
	// 20ミリ秒待機（疑似60FPS）
	WaitTimer(20);
}


