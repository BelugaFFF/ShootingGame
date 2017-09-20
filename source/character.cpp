
#include "character.h"


CHARACTER::CHARACTER() {
	CharaX = STARTPLACE_X;
	CharaY = STARTPLACE_Y;
	GHandle1 = LoadGraph("Graph/character/Chara(player).bmp");
	GHandle_end = LoadGraph("Graph/effect/gameOverEff.bmp");
	move = 1.0f;
	count = 1;
	LifePoint = 4;
	Status = STANDARD;
	invicibleCount = INVICIBLE_TIME;
	gameOverCount = 0;
	
	GetGraphSize(GHandle1, &SizeX, &SizeY);
	if (SizeX < SizeY) ColRadius = (SizeX / 2);
	else ColRadius = (SizeY / 2);

	int w, h;
	GHandle2 = LoadGraph("Graph/ballet/Ballet(blue).bmp");
	GetGraphSize(GHandle2, &w, &h);
	for (int i = 0; i < PSHOT_NUM; i++) {
		shot[i].flag = false;
		shot[i].gh = GHandle2;
		shot[i].width = w;
		shot[i].height = h;
	}

	endflag = FALSE;
}

CHARACTER ::~CHARACTER() {

}

void CHARACTER::Move() {

	if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {

		if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			//移動係数を０．７１に設定
			move = 0.71f;
		}
		else {
			//斜めじゃなければ１．０に設定
			move = 1.0f;
		}
	}
	else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
		move = 1.0f;
	}	
	
	if (key[KEY_INPUT_LEFT] == 1) {
		//左に移動。
		CharaX -= (int)(CHARA_SPEED * move);
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		//右に移動
		CharaX += (int)(CHARA_SPEED * move);
	}
	if (key[KEY_INPUT_UP] == 1) {
		//左に移動。
		CharaY -= (int)(CHARA_SPEED * move);
	}
	if (key[KEY_INPUT_DOWN] == 1) {
		//右に移動
		CharaY += (int)(CHARA_SPEED * move);
	}

	if (CharaX > (WINDOW_WIDTH - SizeX / 2))
		CharaX = (WINDOW_WIDTH - SizeX / 2);
	if (CharaX < (SizeX / 2)) CharaX = (SizeX / 2);

	if (CharaY > (WINDOW_HEIGHT - SizeY / 2))
		CharaY = (WINDOW_HEIGHT - SizeY / 2);
	if (CharaY < (SizeY / 2)) CharaY = (SizeY / 2);
	//todo キャラの移動制限をマクロで定義
}

void CHARACTER::ShotProcess() {
	//キーが押されててかつ、6ループに一回発射
	if (key[KEY_INPUT_Z] == 1 && count % 6 == 0) {
		for (int i = 0; i<PSHOT_NUM; ++i) {
			if (shot[i].flag == false) {
				shot[i].flag = true;
				shot[i].x = CharaX;
				shot[i].y = CharaY;
				break;
			}
		}
	}

	//弾を移動させる処理
	for (int i = 0; i<PSHOT_NUM; ++i) {
		//発射してる弾だけ
		if (shot[i].flag) {
			shot[i].x += PSHOT_SPEED;

			//画面の外にはみ出したらフラグを戻す
			if (shot[i].x > 680) {
				shot[i].flag = false;
			}
		}
	}
}

void CHARACTER::Draw() {
	if(endflag == TRUE) 
		DrawGraph(CharaX - SizeX / 2, CharaY - SizeY / 2, GHandle_end, TRUE);
	else if (Status == ATACKED) {
		if(count % 2 == 0)
			DrawGraph(CharaX - SizeX / 2, CharaY - SizeY / 2, GHandle1, TRUE);
	}
	else DrawGraph(CharaX - SizeX / 2, CharaY - SizeY / 2, GHandle1, TRUE);

	for (int i = 0; i<PSHOT_NUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x - shot[i].width / 2,
				shot[i].y - shot[i].height / 2, shot[i].gh, TRUE);
		}
	}
}

POINT_t CHARACTER ::GetPoint() {
	POINT_t point;
	point.x = CharaX;
	point.y = CharaY;

	return point;
}

int CHARACTER :: GetColRadius() {
	return ColRadius;
}

SHOT_t* CHARACTER :: GetShotInfo() {
	return shot;
}

void CHARACTER::ReceiveTouch() {
	if(Status != ATACKED){
		LifePoint -= 1;
		Status = ATACKED;
	}
}

bool CHARACTER::GameOver() {
	if (gameOverCount < GAMEOVER_TIME) {
		DrawRotaGraph(CharaX, CharaY
			, 1, 0, GHandle_end, TRUE);
		DrawRotaGraph((CharaX - gameOverCount * GAMEOVER_EFF_SPEED), CharaY
			, 1, 0, GHandle_end, TRUE);
		DrawRotaGraph((CharaX + gameOverCount * GAMEOVER_EFF_SPEED), CharaY
			, 1, 0, GHandle_end, TRUE);
		DrawRotaGraph(CharaX, (CharaY - gameOverCount * GAMEOVER_EFF_SPEED)
			, 1, 0, GHandle_end, TRUE);
		DrawRotaGraph(CharaX, (CharaY + gameOverCount * GAMEOVER_EFF_SPEED)
			, 1, 0, GHandle_end, TRUE);
		gameOverCount++;
		return FALSE;
	}

	return TRUE;
}

bool CHARACTER::Manage() {
	if (Status == ATACKED) {
		invicibleCount--;
		if (invicibleCount < 0) {
			Status = STANDARD;
			invicibleCount = INVICIBLE_TIME;
		}
	}

	Move();
	ShotProcess();
	Draw();

	count++;
	if (count > 1000) count = 1;

	if (LifePoint <= 0) {
		endflag = TRUE;
		Status = DEAD;
	}

	return endflag;
}

