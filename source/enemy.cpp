#include"enemy.h"


ENEMY::ENEMY(int type, int stype, int m_pattern, int s_pattern, 
	int in_time, int stop_time, int shot_time, int out_time, 
	int arraivalX, int arraivalY, int speed, int hp, int item) {
	//data init
	x = arraivalX;
	y = arraivalY;
	EnemyType = type;ShotType = stype;
	MovePattern = m_pattern;ShotPattern = s_pattern;
	ArraivalTime = in_time;StopTime = stop_time;
	ShotStartTime = shot_time;OutTime = out_time;
	ShotSpeed = speed;Life = hp;ItemType = item;

	switch (EnemyType) {
	case 0:
		GHandle = LoadGraph("Graph/character/enemy(blue).bmp");
		GHandle_end = LoadGraph("Graph/character/enemy(atacked).bmp");
		CollisionInit(GHandle);
		break;
	case 1:
		GHandle = LoadGraph("Graph/character/enemy(green).bmp");
		GHandle_end = LoadGraph("Graph/character/enemy(atacked).bmp");
		CollisionInit(GHandle);
		break;
	case 2:
		GHandle = LoadGraph("Graph/character/enemy(strong).bmp");
		GHandle_end = LoadGraph("Graph/character/enemy(atacked).bmp");
		CollisionInit(GHandle);
		break;
	case 3:
		//ボス用なので空
		break;
	default:
		GHandle = LoadGraph("Graph/character/errorMsg.bmp");
		break;
	}

	//shot init
	int sizex, sizey;

	switch (ShotType) {
	case 0:
		GHandle_Shot = LoadGraph("Graph/ballet/Ballet(green).bmp");
		GetGraphSize(GHandle_Shot, &sizex, &sizey);
		for (int i = 0; i < PSHOT_NUM; i++) {
			Shot[i].gh = GHandle_Shot;
			Shot[i].width = sizex / 2;
			Shot[i].height = sizey / 2;
		}
		break;
	case 1:
		GHandle_Shot = LoadGraph("Graph/ballet/Ballet(red).bmp");
		GetGraphSize(GHandle_Shot, &sizex, &sizey);
		for (int i = 0; i < PSHOT_NUM; i++) {
			Shot[i].gh = GHandle_Shot;
			Shot[i].width = sizex / 2;
			Shot[i].height = sizey / 2;
		}
		break;
	case 2:
		if (LoadDivGraph("Graph/ballet/Ballet(ball).bmp", 11,
			1, 11,
			19, 18, GHandle_Shot2) == -1)
			DebugMsg("shottype error");
		sizex = 19; sizey = 18;
		for (int i = 0; i < PSHOT_NUM; i++) {
			if(i == 0) Shot[i].gh = GHandle_Shot2[0];
			else Shot[i].gh = GHandle_Shot2[i % 11];
			Shot[i].width = 1;
			Shot[i].height = 1;
		}
		break;
	case 3:
		GHandle_Shot = LoadGraph("Graph/ballet/Ballet(rock).bmp");
		GetGraphSize(GHandle_Shot, &sizex, &sizey);
		for (int i = 0; i < PSHOT_NUM; i++) {
			Shot[i].gh = GHandle_Shot;
			Shot[i].flag = FALSE;
			Shot[i].width = sizex / 2;
			Shot[i].height = sizey / 2;
		}
		break;
	default:
		GHandle = LoadGraph("Graph/character/errorMsg.bmp");
		break;
	}

	//count,anything flag init
	Status = STANDARD;
	count = 1;
	DeadEffCount = 1;
	MoveCount = 0;

	DeadFlag = FALSE;
}

ENEMY :: ~ENEMY() {

}

void ENEMY::CollisionInit(int GH) {
	//collision init
	GetGraphSize(GH, &SizeX, &SizeY);
	if (SizeX < SizeY) ColRadius = (SizeX / 2);
	else ColRadius = (SizeY / 2);
}


void ENEMY::Move() {
	if (!DeadFlag) {
		switch (MovePattern) {
		case 0:
			if (ArraivalTime < count && count < StopTime )
				x -= 3;
			if (OutTime < count) x -= 5;
			break;
		case 1:
			if (ArraivalTime < count && count < StopTime){
				if(MoveCount <= 60){
					x -= (sin(PI / 60 * MoveCount)) * 4;
					MoveCount++;
				}
				else MoveCount = 60;
			}

			if (OutTime < count) {
				if (MoveCount > 30) {
					x -= (sin(PI / 60 * MoveCount)) * 6;
					MoveCount--;
				}
				else x -= 7;
			}
			break;
		case 2:
			if(ArraivalTime < count) x -= 3;
			break;
		case 3:
			if (ArraivalTime < count) x -= 2;
			break;
		case 4:
			if (ArraivalTime < count) {
				x = x - (sin(PI - PI / 120 + PI / 2 + PI / 600 * MoveCount) + 1) * 400;//cos(PI / 6);
				y = y + (sin(PI - PI / 120 + PI / 2 + PI / 600 * MoveCount) + 1) * 480;// sin(PI / 6);
				if (MoveCount < 301) MoveCount++;
			}
			break;
		case 5:
			if (ArraivalTime < count){
				x = x - (sin(PI - PI / 120 + PI / 2 + PI / 600 * MoveCount) + 1) * 400;//cos(PI / 6);
				y = y - (sin(PI - PI / 120 + PI / 2 + PI / 600 * MoveCount) + 1) * 480;// sin(PI / 6);
				if(MoveCount < 301) MoveCount++;
			}
			break;
		case 6:
			if (ArraivalTime < count) {
				if (count < StopTime) {
					x -= 2;
				}
				else {
					y = 240 - sin(PI * 2 / 240 * MoveCount) * 150;
					if (MoveCount > 480) MoveCount = 0;
					else MoveCount++;
				}
			}

			break;
		default :
			DebugMsg("ENEMY->Move 不正な移動パターン");
			break;
		}
	}
}
//*/

void ENEMY :: Draw() {
	switch (Status) {
	case STANDARD:
		DrawGraph(x - SizeX / 2, y - SizeY / 2, GHandle, TRUE);
		break;
	case ATACKED:
		if((count % 4) == 0)
			DrawGraph(x - SizeX / 2, y - SizeY / 2, GHandle_end, TRUE);
		else DrawGraph(x - SizeX / 2, y - SizeY / 2, GHandle, TRUE);
		break;
	case DEAD:
		if(DeadEffCount < 30)
		DrawGraph(x - SizeX / 2, y - SizeY / 2, GHandle_end, TRUE);
		break;
	default:
		DebugMsg("ENEMY,不正なステータス数値");
		break;
	}
	
	for (int i = 0; i < PSHOT_NUM; i++) {
		if(Shot[i].flag)
			DrawRotaGraph(Shot[i].x, Shot[i].y
				, 1, Shot[i].angle, Shot[i].gh, TRUE);//*/
	}
}

void ENEMY::ShotBallet() {
	switch (ShotPattern) {
	case 0:
		PutBallet(0,0,0);
		for (int i = 0; i < PSHOT_NUM; i++) {
			if (Shot[i].flag) {
				Shot[i].x -= ShotSpeed;
			}
		}
		break;
	case 1:
		PutBallet(1,0,0);
		for (int i = 0; i < PSHOT_NUM; i++) {
			if (Shot[i].flag) {
				Shot[i].x -= ShotSpeed;
				Shot[i].y -= sin(Shot[i].angle) * ShotSpeed;
			}

		}
		
		break;
	case 2:
		PutBallet(2,0,0);
		for (int i = 0; i < PSHOT_NUM; i++) {
			if (Shot[i].flag) {
				Shot[i].x -= cos(Shot[i].angle) * ShotSpeed;
				Shot[i].y -= sin(Shot[i].angle) * ShotSpeed;
			}

		}

		break;
	case 3:
		PutBallet(3,0,0);
		for (int i = 0; i < PSHOT_NUM; i++) {
			if (Shot[i].flag) {
				Shot[i].x -= ShotSpeed;
			}
		}

		break;
	case 4:
		DebugMsg("ppp");
		break;
	default:
		DebugMsg("ENEMY::ShotBallet() error!!");
		break;
	}

	for (int i = 0; i < PSHOT_NUM; i++){
		if (Shot[i].x >((Shot[i].width / 2) + WINDOW_WIDTH)
			|| (Shot[i].x + (Shot[i].width / 2)) < 0
			|| Shot[i].y > ((Shot[i].height / 2) + WINDOW_HEIGHT)
			|| (Shot[i].y + (Shot[i].height / 2)) < 0) {
			Shot[i].flag = FALSE;
		}
	}
}

void ENEMY::PutBallet(int option,int px,int py) {
	POINT_t point;
	switch (option) {
	case 0:
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++)
					if (!Shot[j].flag) {
						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						Shot[j].angle = 0;
						break;
					}
			}
		}
		break;
	case 1:
	{
		int putnum = 1;
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++){
					if (!Shot[j].flag) {
						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						switch (putnum) {
						case 1:
							Shot[j].angle = PI / 5;
							break;
						case 2:
							Shot[j].angle = 0;
							break;
						case 3:
							Shot[j].angle = -PI / 5;
							break;
						default:
							DebugMsg("ENEMY::PutBallet() error");
							break;
						}
						putnum++;
					}
					if (putnum == 4) break;
				}
			}
		}
	}
		break;
	case 2:
	{
		int putnum = 1;
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++) {
					if (!Shot[j].flag) {
						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						switch (putnum) {
						case 1:
							Shot[j].angle = PI / 2;
							break;
						case 2:
							Shot[j].angle = 0;
							break;
						case 3:
							Shot[j].angle = -PI / 2;
							break;
						default:
							DebugMsg("ENEMY::PutBallet() error");
							break;
						}
						putnum++;
					}
					if (putnum == 4) break;
				}
			}
		}
	}
		break;
	case 3:
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT2) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++)
					if (!Shot[j].flag) {
						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						Shot[j].angle = 0;
						break;
					}
			}
		}
		break;
	case 4:
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT3) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++)
					if (!Shot[j].flag) {
						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						Shot[j].angle = 0;
						break;
					}
			}
		}
		break;
	case 5:
		if (ShotStartTime < count && Status != DEAD) {
			if ((count % SHOT_LIMIT4) == 0) {
				for (int j = 0; j < PSHOT_NUM; j++)
					if (!Shot[j].flag) {
						point.x = x - px;
						point.y = y - py;

						Shot[j].flag = TRUE;
						Shot[j].x = x;
						Shot[j].y = y;
						Shot[j].angle = atan2(point.y,point.x);
						break;
					}
			}
		}
		break;
	default:
		break;
	}
}

POINT_t ENEMY :: GetPoint() {
	POINT_t point;
	point.x = x;
	point.y = y;

	return point;
}

int ENEMY :: GetColRadius() {
	return ColRadius;
}

int ENEMY::GetShotColRadius() {
	for (int i = 0; i < PSHOT_NUM; i++) {
		if (Shot[i].flag) {
			if (Shot[i].height > Shot[i].width) return Shot[i].width;
			else return Shot[i].height;
		}
	}
}

SHOT_t* ENEMY :: GetShotInfo() {
	return Shot;
}

bool ENEMY :: ConfDeadFlag(){
	if(Status == DEAD) return TRUE;
	else return FALSE;
}

void ENEMY :: ReceiveTouch() {
	Life--;
	Status = ATACKED;
	if (Life <= 0) Status = DEAD;
}

void ENEMY::CountProcess() {
	count++;
	if (count > COUNT_LIM) count = 1;
}

bool ENEMY::GameOver() {//todo 消失描画
	if (DeadEffCount > 30 && CheckMagazineEmpty()) {
		return TRUE;
	}
	else {
		DeadEffCount++;
		return FALSE;
	}
}

bool ENEMY::CheckMagazineEmpty() {
	bool magazineEmptyFlag = TRUE;
	for (int i = 0; i < PSHOT_NUM; i++) {
		if (Shot[i].flag) {
			magazineEmptyFlag = FALSE;
		}
	}
	return magazineEmptyFlag;
}

bool ENEMY :: Manage(POINT_t p) {
	switch (Status) {
	case STANDARD:
		Move();
		ShotBallet();
		Draw();
		break;
	case ATACKED:
		Move();
		ShotBallet();
		Draw();
		break;
	case DEAD:
		DeadFlag = GameOver();
		ShotBallet();
		Draw();
		break;
	default:
		DebugMsg("ENEMY::Manage() error!!");
		break;
	}

	CountProcess();

	if ((count % 50) == 0 && Status != DEAD) Status = STANDARD;
	//ATACKED状態からの復帰

	if ((ArraivalTime + 100) < count && x < (0 - SizeX) || y >(WINDOW_HEIGHT + SizeY))
		Status = DEAD;

	return DeadFlag;
}
