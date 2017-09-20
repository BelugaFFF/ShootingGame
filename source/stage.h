#ifndef STAGE_DEF
#define STAGE_DEF

#include "pch.h"

#define SCROLL_SPEED 1
#define SCROLL_SPEED_ROCK 3
#define SCROLL_SPEED_LITTLEROCK 15
#define DRAW_ROCK_FREQUENCY 1000

#define STAGE1_ENEMYTEAM_1 3
#define STAGE1_ENEMYTEAM_2 2
#define STAGE1_ENEMYTEAM_3 4
#define STAGE1_ENEMYTEAM_4 4
#define STAGE1_ENEMYTEAM_5 3
#define STAGE1_ENEMYTEAM_6 3
#define STAGE1_ENEMYTEAM_7 3
#define STAGE1_ENEMYTEAM_8 2
#define STAGE1_ENEMYTEAM_9 1

#define STAGE1_ENEMY_NUM STAGE1_ENEMYTEAM_1 + STAGE1_ENEMYTEAM_2 + STAGE1_ENEMYTEAM_3 + STAGE1_ENEMYTEAM_4 + STAGE1_ENEMYTEAM_5 + STAGE1_ENEMYTEAM_6 + STAGE1_ENEMYTEAM_7 + STAGE1_ENEMYTEAM_8 + STAGE1_ENEMYTEAM_9
#define BOSS_TEAM STAGE1_ENEMY_NUM - 1

struct BACK_OBJECT_t {
	int x;
	int y;
	bool exist;
};


class STAGE{
protected:
	int SH_back;
	int GH_back;
	int GH_gameover;

	int backCount;
	int effCount;
	bool endflag;
protected:
	STAGE();
	bool initData(FILE**, ENEMYDATA_t*, TCHAR*);
	void DrawBack();
};


class STAGE1 : public STAGE {
private:
	CHARACTER *character;
	ENEMY *enemy[STAGE1_ENEMY_NUM];
	COLLISION *collision;
	int GH_back_obj1, GH_back_obj2;
	int GHsize1_h, GHsize1_w;
	int GHsize2_h, GHsize2_w;
	BACK_OBJECT_t BackObjArray[5];
	int backObjCount;

	int Chapter;
	int EnemyDataRange_start;
	int EnemyDataRange_end;

	bool gameover;
	bool releasekey;

	int soundFlag;//debug
private:
	void DrawBackObj();
	void SoundStop();
	void CollisionProcess();
	void ChangeChapter(int);
	void GameClear();
public:
	STAGE1();
	~STAGE1();

	bool Manage();
};

#endif