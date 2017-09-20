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

			//末尾ならループを抜ける。
			if (c == EOF) {
				return result;
			}

			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n')
				strcat_s(buf, (const char*)&c);
			//カンマか改行ならループ抜ける。
			else
				break;
		}
		//ここに来たということは、1セル分の文字列が出来上がったということ
		switch (col) {
			//1列目は敵種類を表す。atoi関数で数値として代入。
		case 1:	data[row].type = atoi(buf); break;
			//2列目は弾種類。以降省略。
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
		//バッファを初期化
		memset(buf, 0, sizeof(buf));
		//列数を足す
		++col;

		//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n') {
			col = 1;
			++row;
		}
	}
};