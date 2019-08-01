#include "tetris.h"

int main(void) {
	
	WelCome();
	GameBegin();
	while (true)
	{
		NextBlock();
		GamePlay();
	}
	
	return 0;
}

void GamePlay(void) {
	while(next){
		//��������
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY_STOP) {
				_getch();
			}
			else if (key == 224) {				
				int ch = _getch();
				int tmp;
				switch (ch) {
				case KEY_UP: block_dire = rand() % 4; ChangePos(Up, block_dire); break;
				case KEY_DOWN:ChangePos(Down,block_dire); break;
				case KEY_LEFT:ChangePos(Left, block_dire); break;
				case KEY_RIGHT:ChangePos(Right, block_dire); break;
				}
			}
		}
		else {			
			if (Wait(speed)) {
				ChangePos(Down, block_dire);
			}
			
		}

	}

}

void NextBlock(void) {
	//����������飬���ұ���ʾ���л���
	srand(time(NULL));
	block_type = rand() % 4;
	block_dire = rand() % 4;
	BlockPrompt(block[block_type][block_dire][0], blockColor[block_type]);
	Sleep(500);

	//�ҵ���ʼ���У���֤�󷽿�Ӷ�����ʼ����
	int first_one = 0;
	int flat = 0;
	for (int i = 0; i < 5; i++) {
		if (flat == 1) break;
		for (int j = 0; j < 5; j++) {
			if (block[block_type][block_dire][i][j] == 1) {
				flat = 1;
				first_one = i;
				break;
			}
		}
	}
	//����ʾ���鸴�Ƶ���ͼ����
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (block[block_type][block_dire][i][j] == 1) {
				if (map[i - first_one][4 + j] == 1) {
					GameOver();
				}
				map[i - first_one][4 + j] = block[block_type][block_dire][i][j];
				mapColor[i - first_one][4 + j] = blockColor[block_type];
				ppos->x = i - first_one;
				ppos->y = j + 4;
				ppos++;
			}

		}

	}
	DrawMap();
	Sleep(speed);
	//��ԭָ���ַ
	ppos = &pos[0];
	next = 1;
}


void DrawMap(void) {
	for (int i = 0; i < 15; i++) { //��
		for (int j = 0; j < 13; j++) {//��
			if (map[i][j] == 1) {
				DrawBlock(41 + j * BIG_BLOCK_WIDTH, 41 + i * BIG_BLOCK_WIDTH, mapColor[i][j], BIG_BLOCK_WIDTH / 2);
			}
			else {
				DrawBlock(41 + j * BIG_BLOCK_WIDTH, 41 + i * BIG_BLOCK_WIDTH, BLACK, BIG_BLOCK_WIDTH / 2);
			}

		}
	}
	settextcolor(RGB(230, 0, 0));
	settextstyle(40, 0, _T("����"));
	TCHAR str_s[5];
	swprintf_s(str_s, _T("%2d"), score);
	outtextxy(820, 350, str_s);
}


void BlockCleanLine() {
	int checkLine[15] = { 0 };
	for (int i = 0; i < 15; i++) { //��
		int checkSum = 0;
		for (int j = 0; j < 13; j++) {//��
			if (map[i][j] == 1) {
				checkSum++;
			}

		}
		if (checkSum == 13) {
			checkLine[i] = 1;
		}
	}

	for (int i = 14;i >= 0; i--) { //��
		if (checkLine[i] == 1) {
			score += 10;
			for (int j = i; j >= 1; j--) {
				for (int k = 0; k < 13; k++) {
					map[j][k] = map[j - 1][k];
					mapColor[j][k] = mapColor[j - 1][k];
				}
			}
			for (int k = 0; k < 13; k++) {
				map[0][k] = 0;
				mapColor[0][k] = BLACK;
			}
		}
	}
}

void GameOver(void) {
	settextcolor(RGB(230, 0, 0));
	settextstyle(90, 0, _T("����"));
	outtextxy(150, 300, _T("Game Over!"));
	Sleep(10000);
	closegraph();
}

void ChangePos(direction dire, int block_dire) {
	for (int i = 0; i < 4; i++) {
		next_pos[i] = pos[i];
		if (dire == Left) {
			next_pos[i].y -= 1;
		}
		else if (dire == Right) {
			next_pos[i].y += 1;
		}
		else if (dire == Down) {
			next_pos[i].x += 1;
		}
		else if (dire == Up) {
			int first_one = 0;
			int flat = 0;
			for (int i = 0; i < 5; i++) {
				if (flat == 1) break;
				for (int j = 0; j < 5; j++) {
					if (block[block_type][block_dire][i][j] == 1) {
						flat = 1;
						first_one = i;
						break;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (block[block_type][block_dire][i][j] == 1) {
						nppos->x = pos[0].x + i - first_one;
						nppos->y = pos[0].y + j;
						nppos++;
					}

				}

			}
			nppos = &next_pos[0];
		}
	}
	//�ж���һ��λ�������Ƿ�Ϸ�
	int isvalid = 1;
	for (int i = 0; i < 4; i++) {
		if (map[next_pos[i].x][next_pos[i].y] == 1) {
			int find = 0;
			for (int j = 0; j < 4; j++) {
				if (next_pos[i].x == pos[j].x && next_pos[i].y == pos[j].y) {
					find = 1;
					break;
				}
			}
			if (!find) {
				isvalid = 0;
				next = 0;
				break;
			}

		}
		if (next_pos[i].x < 0  || next_pos[i].y < 0 || next_pos[i].y > 12) {
			isvalid = 0;
			break;
		}
		if (next_pos[i].x > 14) {
			isvalid = 0;
			next = 0;
			break;
		}

	}

	if (isvalid) {
		for (int i = 0; i < 4; i++) {
			map[pos[i].x][pos[i].y] = 0;
			mapColor[pos[i].x][pos[i].y] = BLACK;
		}
		for (int i = 0; i < 4; i++) {
			map[next_pos[i].x][next_pos[i].y] = 1;
			mapColor[next_pos[i].x][next_pos[i].y] = blockColor[block_type];
			pos[i] = next_pos[i];
		}
	}
	else {
		BlockCleanLine();
	}
	DrawMap();
	if (dire == Down) {
		Wait(speed);
	}
	


}

bool Wait(int Time) {
	int count = Time / 10;
	for (int i = 0; i < count; i++) {
		if (_kbhit()) {
			return false;
		}
		Sleep(10);
	}
}

void BlockPrompt(int *block, COLORREF color) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (*block == 1) {
				DrawBlock(790 + j * SMALL_BLOCK_WIDTH, 70 + i * SMALL_BLOCK_WIDTH, color, SMALL_BLOCK_WIDTH / 2);
			}
			else {
				DrawBlock(790 + j * SMALL_BLOCK_WIDTH, 70 + i * SMALL_BLOCK_WIDTH, BLACK, SMALL_BLOCK_WIDTH / 2);
			}
			block++;

		}
	}
}

void DrawBlock(int x, int y, COLORREF color, int radius) {
	setlinecolor(BLACK);
	setfillcolor(color);
	fillrectangle(x - radius, y - radius, x + radius, y + radius);
}

void WelCome(void) {
	initgraph(1000, 820);
	settextstyle(60, 0, _T("����"));
	outtextxy(350, 300, _T("����˹����"));
	Sleep(3000);

}

void GameBegin(void) {
	cleardevice();

	setlinecolor(RGB(230, 230, 230));
	setlinestyle(PS_SOLID, 5);
	rectangle(10, 10, 696, 800);

	setlinestyle(PS_SOLID, 4);
	rectangle(730, 10, 980, 260);
	settextcolor(RGB(230, 0, 0));
	settextstyle(40, 0, _T("����"));
	//�����ʼ����
	outtextxy(800, 300, _T("������"));
	TCHAR str_s[5];
	swprintf_s(str_s, _T("%2d"), score);
	outtextxy(820, 350, str_s);
	//�����ʼ�ȼ�
	outtextxy(800, 420, _T("�ȼ���"));
	TCHAR str_r[5];
	swprintf_s(str_r, _T("%d"), score);
	outtextxy(830, 470, str_r);
	//����淨
	settextcolor(RGB(128, 0, 250));
	settextstyle(30, 0, _T("����"));
	outtextxy(760, 530, _T("��Ϸ�淨��"));
	outtextxy(760, 570, _T("�ո���ͣ"));
	outtextxy(760, 610, _T("��������"));
	outtextxy(760, 650, _T("���������ƶ�"));
	outtextxy(760, 690, _T("���������ƶ�"));
	outtextxy(760, 730, _T("���������ƶ�"));

}