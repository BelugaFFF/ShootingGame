#include"collision.h"



COLLISION :: COLLISION(){

}

COLLISION :: ~COLLISION() {
}

bool COLLISION :: CheckTouch() {
	double distance;
	unsigned int disX, disY;

	if(0 >= CompX || CompX >= WINDOW_WIDTH 
		|| 0 >= CompY || CompY >= WINDOW_HEIGHT) return FALSE;

	disX = OwnX - CompX;
	disY = OwnY - CompY;

	distance = sqrt((disX * disX) + (disY * disY));
	if ((int)distance <= (OwnRadius + CompRadius)) {
		return TRUE;
	}
	else return FALSE;
}

void COLLISION::ReceiveVal(POINT_t point1, int radius1,
	POINT_t point2, int radius2) {
	OwnX = point1.x; OwnY = point1.y;
	OwnRadius = radius1;
	CompX = point2.x; CompY = point2.y;
	CompRadius = radius2;
}


bool COLLISION::Manage(POINT_t point1, int radius1,
	POINT_t point2, int radius2) {
	ReceiveVal(point1, radius1, point2, radius2);

	return CheckTouch();
}//*/

//new process
/*bool COLLISION::CheckTouch() {
	int w, h;
	if (CompX1 <= OwnX && OwnX <= CompX2) w = TRUE;
	if()

	if (w && h) return TRUE;
	else return FALSE;
}

bool COLLISION::CheckTouch_RR

bool COLLISION::Manage(POINT_t p1,COLLISION_t c1,POINT_t p2,COLLISION_t c2) {
	int ctype = 0X00;
	if (c1.colltype == ROUND) ctype = ctype | 0X01;
	if (c2.colltype == ROUND) ctype = ctype | 0X02;

	switch (ctype) {
	case 0://SQUARE-S
		
		break;
	case 1://ROUND-S
		break;
	case 2://S-R
		break;
	case 3://R-R

		break;
	default:
		
		return FALSE;
	}
}//*/
