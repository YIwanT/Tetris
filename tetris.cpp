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
		//按键控制
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
	//产生随机方块，在右边提示框中画出
	srand(time(NULL));
	block_type = rand() % 4;
	block_dire = rand() % 4;
	BlockPrompt(block[block_type][block_dire][0], blockColor[block_type]);
	Sleep(500);

	//找到开始的行，保证大方块从顶部开始下落
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
	//将提示方块复制到地图数组
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
	//还原指针地址
	ppos = &pos[0];
	next = 1;
}


void DrawMap(void) {
	for (int i = 0; i < 15; i++) { //行
		for (int j = 0; j < 13; j++) {//列
			if (map[i][j] == 1) {
				DrawBlock(41 + j * BIG_BLOCK_WIDTH, 41 + i * BIG_BLOCK_WIDTH, mapColor[i][j], BIG_BLOCK_WIDTH / 2);
			}
			else {
				DrawBlock(41 + j * BIG_BLOCK_WIDTH, 41 + i * BIG_BLOCK_WIDTH, BLACK, BIG_BLOCK_WIDTH / 2);
			}

		}
	}
	settextcolor(RGB(230, 0, 0));
	settextstyle(40, 0, _T("宋体"));
	TCHAR str_s[5];
	swprintf_s(str_s, _T("%2d"), score);
	outtextxy(820, 350, str_s);
}


void BlockCleanLine() {
	int checkLine[15] = { 0 };
	for (int i = 0; i < 15; i++) { //行
		int checkSum = 0;
		for (int j = 0; j < 13; j++) {//列
			if (map[i][j] == 1) {
				checkSum++;
			}

		}
		if (checkSum == 13) {
			checkLine[i] = 1;
		}
	}

	for (int i = 14;i >= 0; i--) { //行
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
	settextstyle(90, 0, _T("宋体"));
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
	//判断下一个位置数组是否合法
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
	settextstyle(60, 0, _T("宋体"));
	outtextxy(350, 300, _T("俄罗斯方块"));
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
	settextstyle(40, 0, _T("宋体"));
	//输出初始分数
	outtextxy(800, 300, _T("分数："));
	TCHAR str_s[5];
	swprintf_s(str_s, _T("%2d"), score);
	outtextxy(820, 350, str_s);
	//输出初始等级
	outtextxy(800, 420, _T("等级："));
	TCHAR str_r[5];
	swprintf_s(str_r, _T("%d"), score);
	outtextxy(830, 470, str_r);
	//输出玩法
	settextcolor(RGB(128, 0, 250));
	settextstyle(30, 0, _T("宋体"));
	outtextxy(760, 530, _T("游戏玩法："));
	outtextxy(760, 570, _T("空格：暂停"));
	outtextxy(760, 610, _T("↑：变形"));
	outtextxy(760, 650, _T("↓：向下移动"));
	outtextxy(760, 690, _T("←：向左移动"));
	outtextxy(760, 730, _T("→：向右移动"));

}