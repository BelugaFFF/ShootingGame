#ifndef CHARACTER_H
#define CHARACTER_H

#include"pch.h"

#define CHARA_SPEED 10 
#define STARTPLACE_X 100
#define STARTPLACE_Y 100
#define INVICIBLE_TIME 150
#define GAMEOVER_TIME 50
#define GAMEOVER_EFF_SPEED 10  

class CHARACTER{
private:
	int CharaX, CharaY;
	int SizeX, SizeY;
	int GHandle1,GHandle2;
	int GHandle_end;

	double CharaVel;//‰Á‘¬“x
	float move;

	int LifePoint;
	STATUS_e Status;

	bool endflag;
	int ColRadius;

	int count;
	int invicibleCount;
	int gameOverCount;
public:
	SHOT_t shot[PSHOT_NUM];
private:
	void ShotProcess();
	void Move();
	void Draw();

public:
	CHARACTER();
	~CHARACTER();// content is nothing

	POINT_t GetPoint();
	int GetColRadius();
	SHOT_t* GetShotInfo();

	void ReceiveTouch();
	bool GameOver();

	bool Manage();
};

#endif