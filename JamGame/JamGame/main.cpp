#include "DxLib.h"
#include "GameSystem.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	GameSystem* game_system = new GameSystem();
	if (DxLib_Init() == -1) { return -1; }
	game_system->init();

	while (1) {
		game_system->gameLoopPre();

		game_system->gameLoop();

		game_system->gameLoopPost();
		if (ProcessMessage() == -1) { break; }
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) { break; }
	}

	//Dxƒ‰ƒCƒuƒ‰ƒŠI—¹ˆ—
	DxLib_End();

	return 0;
}