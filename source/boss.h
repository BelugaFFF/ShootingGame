#ifndef BOSS_H
#define BOSS_H
#include"pch.h"

class BOSS : public ENEMY{
private:
	int GHandle_Boss[4]; int GHandle_eff;
	int GHandle_end[2];
	int GHandle_atacked;

	int StatusCount;
	int StatusCount2;

	int motioncount;
protected:
	void Draw();
	void ShotBallet(int, POINT_t);
	void MoveBallet();
	void StatusChange();
	bool GameOver();
public:
	BOSS(int type, int stype, int m_pattern, int s_pattern,
		int in_time, int stop_time, int shot_time, int out_time,
		int x, int y, int speed, int hp, int item);
	~BOSS();

	void ReceiveTouch();
	bool Manage(POINT_t);
};

#endif // !BOSS_H
