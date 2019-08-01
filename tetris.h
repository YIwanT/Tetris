#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <graphics.h>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>


#define BIG_BLOCK_WIDTH	52
#define SMALL_BLOCK_WIDTH	30

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_LEFT	75	
#define KEY_RIGHT	77	
#define KEY_STOP	32

using namespace std;

typedef enum _direction {
	Left,
	Right,
	Up,
	Down
}direction;


int score = 0;
int rank = 0;

int block_type = -1;
int block_dire = -1;

int speed = 500;

int next = 1;


typedef struct block_pos {
	int x;
	int y;
}block_pos;

block_pos pos[4];
block_pos next_pos[4];
block_pos change_pos[4];

block_pos *ppos = &pos[0];
block_pos *nppos = &next_pos[0];

COLORREF blockColor[4] = { GREEN,LIGHTBLUE,LIGHTRED,YELLOW };
//游戏区域数组
int map[15][13] = { 0 };
COLORREF mapColor[15][13] = { BLACK };

//方块数组

int block[4][4][5][5] = {
	{
		{ 0,0,0,0,0,
		0,1,0,0,0,
		0,1,0,0,0,
		0,1,1,0,0,
		0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,1,0,
	0,1,1,1,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,1,1,0,
	0,0,0,1,0,
	0,0,0,1,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,1,1,1,0,
	0,1,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0
		}
	},
	{
		{ 0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	1,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0
		},
		{ 0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	1,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0
		}
	},
	{
		{ 0,0,0,0,0,
		0,0,0,0,0,
		0,0,1,1,0,
		0,0,1,1,0,
		0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	0,0,1,1,0,
	0,0,1,1,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	0,0,1,1,0,
	0,0,1,1,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,0,0,
	0,0,1,1,0,
	0,0,1,1,0,
	0,0,0,0,0
		}
	},
	{
		{ 0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,0,
	0,0,1,0,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,1,1,0,
	0,1,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0
		},
		{ 0,0,0,0,0,
	0,0,0,1,0,
	0,0,1,1,0,
	0,0,1,0,0,
	0,0,0,0,0
		}
	}
};

void WelCome(void);

void GameBegin(void);

void GamePlay(void);

void DrawBlock(int x, int y, COLORREF color, int radius);

void BlockPrompt(int *block, COLORREF color);

void ChangePos(direction dire, int block_dire);

void DrawMap(void);

void NextBlock(void);

bool Wait(int Time);

void BlockCleanLine(void);

void GameOver(void);


#endif // !_TETRIS_H_

