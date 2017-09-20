#ifndef COLLISION_
#define COLLISION_
#include"pch.h"

class COLLISION {
private:
	int OwnX, OwnY;//notise...this point is center 
						//of the collision detection.
	int OwnRadius;
	int CompX, CompY;
	
	int CompX1, CompX2;
	int CompY1, CompY2;
	
	int CompRadius;

	bool GameOverFlag;
private:
	bool CheckTouch();
public:
	COLLISION();
	~COLLISION();

	void ReceiveVal(POINT_t, int,POINT_t, int);
	bool Manage(POINT_t,int,POINT_t,int);
};

#endif
