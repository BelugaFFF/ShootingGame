#include"pch.h"


char key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetTransColor(255, 255, 255);

	STAGE1 *stage1 = new STAGE1;
	printfDx("\n\n	----HOW TO PLAY---\n");
	printfDx("\n\n	[esc]KEY -> END\n\n");
	printfDx("	[Z]KEY -> SHOT\n\n	[©][ª][«][¨]KEY -> MOVE \n\n");
	printfDx("\n\n	HIT KEY!!\n\n");
	ScreenFlip();
	WaitKey();
	clsDx();
	ClearDrawScreen();
	
	while (ScreenFlip() == 0
		&& ProcessMessage() == 0
		&& ClearDrawScreen() == 0
		&& GetHitKeyStateAll(key) == 0)
	{
		if (stage1->Manage()) break;
		if (key[KEY_INPUT_ESCAPE] == 1) break;
	}

	delete stage1;

	DxLib_End();
	return 0;
}