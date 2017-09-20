#include"boss.h"

BOSS :: BOSS(int type, int stype, int m_pattern, int s_pattern,
	int in_time, int stop_time, int shot_time, int out_time,
	int x, int y, int speed, int hp, int item)
	:ENEMY(type,stype,m_pattern,s_pattern,
		in_time,stop_time,shot_time,out_time,
		x,y,speed,hp,item)
{
	GHandle_Boss[0] = LoadGraph("Graph/character/enemy(boss1).bmp");
	GHandle_Boss[1] = LoadGraph("Graph/character/enemy(boss2).bmp");
	GHandle_Boss[2] = LoadGraph("Graph/character/enemy(boss3).bmp");
	GHandle_Boss[3] = LoadGraph("Graph/character/enemy(boss4).bmp");
	GHandle_atacked = LoadGraph("Graph/character/enemy(boss.atacked).bmp");
	GHandle_end[0] = LoadGraph("Graph/character/enemy(boss.end).bmp");
	GHandle_end[1] = LoadGraph("Graph/character/enemy(boss.end2).bmp");

	CollisionInit(GHandle_Boss[0]);
	StatusCount = 0;
	StatusCount2 = 0;

	motioncount = 0;
}

BOSS :: ~BOSS() {

}

void BOSS::Draw() {
	switch (Status) {
	case STANDARD:
		switch (motioncount % 4)
		{
		case 0:
			DrawRotaGraph(x, y
				, 1, 0, GHandle_Boss[0], TRUE);
			break;
		case 1:
			DrawRotaGraph(x, y
				, 1, 0, GHandle_Boss[1], TRUE);
			break;
		case 2:
			DrawRotaGraph(x, y
				, 1, 0, GHandle_Boss[2], TRUE);
			break;
		case 3:
			DrawRotaGraph(x, y
				, 1, 0, GHandle_Boss[3], TRUE);
			break;
		default:
			break;
		}
		break;
	case ATACKED:
		if (count % 2 == 0)
			DrawRotaGraph(x, y, 1, 0, GHandle_atacked, TRUE);
		else DrawRotaGraph(x, y, 1, 0, GHandle_Boss[3], TRUE);
		break;
	case ATACK:
		DrawRotaGraph(x, y, 1, 0, GHandle_Boss[3], TRUE);
		break;
	default:
		break;
	}

	for (int i = 0; i < PSHOT_NUM; i++) {
		if (Shot[i].flag)
			DrawRotaGraph(Shot[i].x, Shot[i].y
				, 1, Shot[i].angle, Shot[i].gh, TRUE);//*/
	}
	
	if ((count % 5) == 0) motioncount++;
	if (motioncount > 40) motioncount = 0;
}

void BOSS::ShotBallet(int option,POINT_t p) {
	switch (option) {
	case 0:
		PutBallet(4, p.x, p.y);
		MoveBallet();
		break;
	case 1:
		PutBallet(5, p.x, p.y);
		MoveBallet();
		break;
	default:
		break;
	}
}

void BOSS::MoveBallet() {
	for (int i = 0; i < PSHOT_NUM; i++) {
		if (Shot[i].flag) {
			if(Shot[i].angle == 0) Shot[i].x -= ShotSpeed;
			else {
				Shot[i].x -= cos(Shot[i].angle) * 8;
				Shot[i].y -= sin(Shot[i].angle) * 8;
			}
		}
	}

	for (int i = 0; i < PSHOT_NUM; i++) {
		if (Shot[i].x >((Shot[i].width / 2) + WINDOW_WIDTH)
			|| (Shot[i].x + (Shot[i].width / 2)) < 0
			|| Shot[i].y > ((Shot[i].height / 2) + WINDOW_HEIGHT)
			|| (Shot[i].y + (Shot[i].height / 2)) < 0) {
			Shot[i].flag = FALSE;
		}
	}
}

bool BOSS::GameOver() {
	if (y > (WINDOW_HEIGHT + 200) && CheckMagazineEmpty()) {
		return TRUE;
	}
	else {
		y += 2;
		if (count % 2 == 0)
			DrawRotaGraph(x, y, 1, PI / 100 * DeadEffCount, GHandle_end[0], TRUE);
		else DrawRotaGraph(x, y, 1, PI / 100 * DeadEffCount, GHandle_end[1], TRUE);
		DeadEffCount++;
		return FALSE;
	}
}

void  BOSS::ReceiveTouch() {
	if (Status != STANDARD) {
		Life--;
		Status = ATACKED;
	}
	if (Life <= 0) Status = DEAD;
}

void  BOSS::StatusChange() {
	switch (Status) {
	case STANDARD:
		if (StatusCount >= 300) {
			Status = ATACK;
			StatusCount = 0;
		}
		break;
	case ATACKED:
		if (StatusCount2 >= 30) {
			Status = ATACK;
			StatusCount2 = 0;
		}
		else StatusCount2++;

		if (StatusCount >= 200) {
			Status = STANDARD;
			StatusCount = 0;
		}
		break;
	case ATACK:
		if (StatusCount >= 200) {
			Status = STANDARD;
			StatusCount = 0;
		}
		break;//todo
	default:
		break;
	}
}

bool BOSS :: Manage(POINT_t p) {
	switch (Status) {
	case STANDARD:
		ShotBallet(0, p);
		Move();
		Draw();
		if(count > StopTime) StatusChange();
		StatusCount++;
		break;
	case ATACKED:
		ShotBallet(1,p);
		Move();
		Draw();
		StatusChange();
		break;
	case DEAD:
		MoveBallet();
		Draw();
		DeadFlag = GameOver();
		break;
	case ATACK:
		ShotBallet(1,p);
		Move();
		Draw();
		StatusChange();
		break;//todo
	default:
		break;
	}
	
	StatusCount++;
	CountProcess(); 
	return DeadFlag;
}