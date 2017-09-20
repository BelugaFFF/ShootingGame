#include"stage.h"

STAGE::STAGE() {
	backCount = WINDOW_WIDTH;
	effCount = 0;
	endflag = FALSE;
	GH_gameover = LoadGraph("Graph/word/gameover.bmp");
}

void STAGE::DrawBack() {
	DrawGraph(backCount, 0,GH_back,TRUE);
	DrawGraph(backCount - WINDOW_WIDTH, 0, GH_back, TRUE);

	if (backCount > 0) backCount -= SCROLL_SPEED;
	else backCount = WINDOW_WIDTH;
}

bool STAGE::initData(FILE **fp, ENEMYDATA_t *data, TCHAR *fileName) {
	errno_t err;
	char buf[100];
	int c;
	int col = 1;
	int row = 0;
	bool result;

	memset(buf, 0, sizeof(buf));
	err = fopen_s(fp, fileName, "r");
	if (err == 0) {
		printfDx("File was opened.\n");
		result = TRUE;
	}
	else {
		printfDx("File was not finded!!\nerr = %d\n", err);
		result = FALSE;
		return result;
	}
	while (fgetc(*fp) != '\n');

	while (1) {

		while (1) {

			c = fgetc(*fp);

			//�����Ȃ烋�[�v�𔲂���B
			if (c == EOF) {
				return result;
			}

			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
				strcat_s(buf, (const char*)&c);
			//�J���}�����s�Ȃ烋�[�v������B
			else
				break;
		}
		//�����ɗ����Ƃ������Ƃ́A1�Z�����̕����񂪏o���オ�����Ƃ�������
		switch (col) {
			//1��ڂ͓G��ނ�\���Batoi�֐��Ő��l�Ƃ��đ���B
		case 1:	data[row].type = atoi(buf); break;
			//2��ڂ͒e��ށB�ȍ~�ȗ��B
		case 2: data[row].stype = atoi(buf); break;
		case 3: data[row].m_pattern = atoi(buf); break;
		case 4: data[row].s_pattern = atoi(buf); break;
		case 5: data[row].in_time = atoi(buf); break;
		case 6: data[row].stop_time = atoi(buf); break;
		case 7: data[row].shot_time = atoi(buf); break;
		case 8: data[row].out_time = atoi(buf); break;
		case 9: data[row].x = atoi(buf); break;
		case 10: data[row].y = atoi(buf); break;
		case 11: data[row].speed = atoi(buf); break;
		case 12: data[row].hp = atoi(buf); break;
		case 13: data[row].item = atoi(buf); break;
		}
		//�o�b�t�@��������
		memset(buf, 0, sizeof(buf));
		//�񐔂𑫂�
		++col;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n') {
			col = 1;
			++row;
		}
	}
};