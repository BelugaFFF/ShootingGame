#ifndef DEFINE_H
#define DEFINE_H

#define PI 3.141592654f

//window size
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define COUNT_LIM 10000000

//�L�[������Ԋi�[�ϐ�
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
	bool flag;//�e�����˒����ǂ���
	double x;//x���W
	double y;//y���W
	double angle;
	COLLISION_t coll;
	int gh;//�O���t�B�b�N�n���h��
	int width, height;//�摜�̕��ƍ���
};

enum STATUS_e{
	STANDARD,
	ATACKED,
	DEAD,
	ATACK
};

//ENEMY
struct ENEMYDATA_t {
	int type;//�G���
	int stype;//�e���
	int m_pattern;//�ړ��p�^�[��
	int s_pattern;//���˃p�^�[��
	int in_time;//�o������
	int stop_time;//��~����
	int shot_time;//�e���ˎ���
	int out_time;//�ޏꎞ��
	int x;//x���W
	int y;//y���W
	int speed;//�e�X�s�[�h
	int hp;//HP
	int item;//�A�C�e��
};
#endif