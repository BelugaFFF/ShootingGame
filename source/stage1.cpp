
#include"stage.h"
//#define DATA "Data/Stage1_Enemy1.csv"
#define DATA "Data/Stage1_Enemy2.csv"

STAGE1::STAGE1() {
	gameover = FALSE;
	SH_back = LoadSoundMem("Sound/bgm/bgm.wav");
	GH_back = LoadGraph("Graph/back/backtest1.bmp");
	GH_back_obj1 = LoadGraph("Graph/back/rock2.bmp");
	GH_back_obj2 = LoadGraph("Graph/back/little_rock.bmp");

	int Wsize, Hsize;
	GetGraphSize(GH_back_obj1, &Wsize, &Hsize);
	GHsize1_w = Wsize;
	GHsize1_h = Hsize;
	GetGraphSize(GH_back_obj2, &Wsize, &Hsize);
	GHsize2_w = Wsize;
	GHsize2_h = Hsize;
	backObjCount = SCROLL_SPEED_ROCK * DRAW_ROCK_FREQUENCY;

	for (int i = 0; i < 5; i++) BackObjArray[i].exist = FALSE;

	//enemy class initialize to input csv file.

	FILE *fp;
	ENEMYDATA_t data[STAGE1_ENEMY_NUM];

	if (initData(&fp, data, DATA)) {//debug
		printfDx("initData() was processed.\n");
		fclose(fp);
	}
	else {
		printfDx("initData() was failed!!\n");
	}

	for (int i = 0; i< STAGE1_ENEMY_NUM; ++i) {
		if (i == BOSS_TEAM) {
			enemy[i] = new BOSS(data[i].type, data[i].stype,
				data[i].m_pattern, data[i].s_pattern,
				data[i].in_time, data[i].stop_time, data[i].shot_time,
				data[i].out_time, data[i].x, data[i].y,
				data[i].speed, data[i].hp, data[i].item);
		}
		else {
			enemy[i] = new ENEMY(data[i].type, data[i].stype,
				data[i].m_pattern, data[i].s_pattern,
				data[i].in_time, data[i].stop_time, data[i].shot_time,
				data[i].out_time, data[i].x, data[i].y,
				data[i].speed, data[i].hp, data[i].item);
		}
	}

	character = new CHARACTER;
	collision = new COLLISION;

	releasekey = TRUE;

	Chapter = 0;
	EnemyDataRange_start = 0;
	EnemyDataRange_end = 0;
	ChangeChapter(0);//!0 -> Debug mode(Chapter select)
	
	soundFlag = 1;
}

STAGE1::~STAGE1() {
	for (int i = 0; i < STAGE1_ENEMY_NUM; ++i) {
		if(enemy[i] != NULL) delete enemy[i];
	}
	delete character;
	delete collision;
}

bool  STAGE1::Manage() {
	//debug sound process
	SoundStop();
	//draw back bmp
	DrawBack();
	DrawBackObj();

	//character drawing
	bool enemyEmptyFlag = TRUE;
	for (int i = EnemyDataRange_start; i < EnemyDataRange_end; ++i) {
		if (enemy[i] != NULL) {
			if (i == BOSS_TEAM) {
				//boss用処理
				enemyEmptyFlag = FALSE;
				if (enemy[i]->Manage(character->GetPoint())) {
					delete enemy[i];
					enemy[i] = NULL;
				}
			}
			else {
				enemyEmptyFlag = FALSE;
				if (enemy[i]->Manage(character->GetPoint())) {
					delete enemy[i];
					enemy[i] = NULL;
				}
			}
		}
	}

	if (enemyEmptyFlag) ChangeChapter(0);
	//引数常に0、モード変更はコンストラクタで

	if (!endflag)
		endflag = character->Manage();
	else if (character->GameOver())
		DrawGraph(0, 0, GH_gameover, TRUE);

	//collision
	CollisionProcess();

	return gameover;
}


void STAGE1::DrawBackObj() {
	if(backObjCount <= SCROLL_SPEED_ROCK)
		backObjCount
		= SCROLL_SPEED_ROCK * DRAW_ROCK_FREQUENCY;

	if ((backObjCount % (400 + effCount)) == 0) {
		POINT_t t = character->GetPoint();
		srand(t.x + t.y + backCount + effCount);

		for (int j = 0; j < 5; j++) {
			if (BackObjArray[j].exist == FALSE) {
				BackObjArray[j].exist = TRUE;
				BackObjArray[j].x = WINDOW_WIDTH + 100;
				BackObjArray[j].y
				= (rand() % (WINDOW_HEIGHT - GHsize1_h));
				break;
			}
		}
		effCount = rand() % 100;
	}

	for (int i = 0; i < 5; i++) {
		if (BackObjArray[i].exist == TRUE) {
			DrawRotaGraph(BackObjArray[i].x, BackObjArray[i].y
				, 1, (2 * PI / 2500) * (backObjCount % 2501), GH_back_obj1, TRUE);
			/*DrawGraph(BackObjArray[i].x, BackObjArray[i].y,
				GH_back_obj1, TRUE);//*/
			BackObjArray[i].x -= SCROLL_SPEED_ROCK;

		}

		if (BackObjArray[i].x < (-1 * GHsize1_w))
			BackObjArray[i].exist = FALSE;
	}

	backObjCount -= SCROLL_SPEED_ROCK;
}

void STAGE1::SoundStop() {
	if (soundFlag == 1)
		PlaySoundMem(SH_back, DX_PLAYTYPE_LOOP, FALSE);
	else
		StopSoundMem(SH_back);

	if (key[KEY_INPUT_S] == 1 && releasekey == TRUE) {
		soundFlag *= -1;
		releasekey = FALSE;
	}
	if (key[KEY_INPUT_S] == 0) releasekey = TRUE;
}

void STAGE1::CollisionProcess() {
	SHOT_t *es, *cs;
	POINT_t eshotP, cshotP;
	for (int i = EnemyDataRange_start; i < EnemyDataRange_end; ++i) {
		if (enemy[i] != NULL) {
			if (!enemy[i]->ConfDeadFlag()) {
				if (collision->Manage(
					character->GetPoint(),
					character->GetColRadius(),
					enemy[i]->GetPoint(),
					enemy[i]->GetColRadius()
				))character->ReceiveTouch();
			}

			es = enemy[i]->GetShotInfo();
			for (int j = 0; j < SHOT_LIMIT; j++) {
				if (es[j].flag) {
					eshotP.x = es[j].x;
					eshotP.y = es[j].y;
					if (collision->Manage(
						character->GetPoint(),
						character->GetColRadius(),
						eshotP,
						enemy[i]->GetShotColRadius()
					))character->ReceiveTouch();
				}
			}

			cs = character->GetShotInfo();
			for (int k = 0; k < PSHOT_NUM; k++) {
				if (cs[k].flag) {
					cshotP.x = cs[k].x;
					cshotP.y = cs[k].y;
					if (collision->Manage(
						cshotP, 1,
						enemy[i]->GetPoint(),
						enemy[i]->GetColRadius()
					))enemy[i]->ReceiveTouch();
				}
			}
		}

	}
}

void STAGE1::ChangeChapter(int mode) {
	int i = 0;

	bool debugmode = FALSE;
	if (mode != 0) debugmode = TRUE;
	
	do {
		switch (Chapter){
		case 0:
			EnemyDataRange_start = 0;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1;

			Chapter++;
			break;
		case 1:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2;

			Chapter++;
			break;
		case 2:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3;

			Chapter++;
			break;
		case 3:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4;

			Chapter++;
			break;
		case 4:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4
				+ STAGE1_ENEMYTEAM_5;

			Chapter++;
			break;
		case 5:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4
				+ STAGE1_ENEMYTEAM_5 + STAGE1_ENEMYTEAM_6;

			Chapter++;
			break;
		case 6:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4
				+ STAGE1_ENEMYTEAM_5 + STAGE1_ENEMYTEAM_6
				+ STAGE1_ENEMYTEAM_7;

			Chapter++;
			break;
		case 7:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4
				+ STAGE1_ENEMYTEAM_5 + STAGE1_ENEMYTEAM_6
				+ STAGE1_ENEMYTEAM_7 + STAGE1_ENEMYTEAM_8;
			Chapter++;
			break;
		case 8:
			EnemyDataRange_start = EnemyDataRange_end;
			EnemyDataRange_end = STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2
				+ STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4
				+ STAGE1_ENEMYTEAM_5 + STAGE1_ENEMYTEAM_6
				+ STAGE1_ENEMYTEAM_7 + STAGE1_ENEMYTEAM_8
				+ STAGE1_ENEMYTEAM_9;
			Chapter++;
			break;
		default:
			GameClear();
			break;
		}

		if (!debugmode) break;
		else i++;
	} while (i <= mode);
}

void STAGE1::GameClear() {
	DebugMsg("game clear!!");
	gameover = TRUE;
	//todo
}