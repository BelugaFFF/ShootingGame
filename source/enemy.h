#ifndef ENEMY_
#define ENEMY_

#include"pch.h"

#define SHOT_LIMIT 30
#define SHOT_LIMIT2 3
#define SHOT_LIMIT3 40
#define SHOT_LIMIT4 9

#define SHOT_SPEED 10

class ENEMY {
protected:
	int x, y;
	int SizeX, SizeY;

	int EnemyType; int ShotType;
	int MovePattern; int ShotPattern;
	int ArraivalTime; int StopTime;
	int ShotStartTime; int OutTime;
	int ShotSpeed; int Life; int ItemType;
	int GHandle; 
	int GHandle_end;
	
	int GHandle_Shot;
	int GHandle_Shot2[11];

	bool DeadFlag;
	int ColRadius;
	STATUS_e Status;
	
	int count;
	int DeadEffCount;
	int MoveCount;
public:
	SHOT_t Shot[PSHOT_NUM];

protected:
	void Move();
	void Draw();
	virtual void ShotBallet();
	void PutBallet(int,int,int);
	void CollisionInit(int);
	bool GameOver();
	bool CheckMagazineEmpty();
public:
	ENEMY(int type, int stype, int m_pattern, int s_pattern, 
		int in_time, int stop_time, int shot_time, int out_time, 
		int x, int y, int speed, int hp, int item);
	~ENEMY();

	POINT_t GetPoint();
	int GetColRadius();
	int GetShotColRadius();
	SHOT_t* GetShotInfo();
	bool ConfDeadFlag();
	virtual void ReceiveTouch();
	void CountProcess();
	

	virtual bool Manage(POINT_t);
};

#endif
