#ifndef DEFINE_H
#define DEFINE_H

#define PI 3.141592654f

//window size
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define COUNT_LIM 10000000

//キー押下状態格納変数
extern char key[];

//standard struct
struct POINT_t{
	int x;
	int y;
};

enum COLL_TYPE_e {
	SQUARE,
	ROUND
};

struct COLLISION_t {
	COLL_TYPE_e colltype;
	POINT_t t1;
	POINT_t t2;
};

//CHARACTER

//shot
#define PSHOT_NUM 30
#define PSHOT_SPEED 30

struct SHOT_t{
	bool flag;//弾が発射中かどうか
	double x;//x座標
	double y;//y座標
	double angle;
	COLLISION_t coll;
	int gh;//グラフィックハンドル
	int width, height;//画像の幅と高さ
};

enum STATUS_e{
	STANDARD,
	ATACKED,
	DEAD,
	ATACK
};

//ENEMY
struct ENEMYDATA_t {
	int type;//敵種類
	int stype;//弾種類
	int m_pattern;//移動パターン
	int s_pattern;//発射パターン
	int in_time;//出現時間
	int stop_time;//停止時間
	int shot_time;//弾発射時間
	int out_time;//退場時間
	int x;//x座標
	int y;//y座標
	int speed;//弾スピード
	int hp;//HP
	int item;//アイテム
};
#endif